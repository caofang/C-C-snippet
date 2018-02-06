#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h> // date and time for log file
#include <signal.h> // for signaling
#include <sys/wait.h> // for using wait(), WIFEXITED(), WIFEXITSTATUS()

/* DEFINITIONS */

// Miscellaneous
#define LOG_FILENAME "/usr/sensoredge/udp_listener_log"
#define DEBUGLOG_FILENAME "/usr/sensoredge/debug_log"
// UDP stuff
#define LISTEN_PORT "4952" // this port
#define DEST_PORT "4950"   // destination client port for streaming
#define MAXBUFLEN 100 // control received
// MeX Box stuff
#define MX_CMD " "
#define MX_CMD_LENGTH 32 // account for string termination character
#define READ_SIZE 4095
#define MAX_LOOPS 50
#define BOX_LAG_TIME_US 1000
// MeX Box 
#define BYTES_PER_SENSEL 2
#define FRAME_HEIGHT 32
#define FRAME_WIDTH 64
#define FRAMES_PER_REQUEST 4
#define BYTES_PER_FRAME FRAME_HEIGHT * FRAME_WIDTH * BYTES_PER_SENSEL
//
#define PACKETS_PER_FRAME 8
#define BYTES_PER_PACKET BYTES_PER_FRAME / PACKETS_PER_FRAME
#define PACKET_FRAME_NUMBER_SIZE 4
#define PACKET_SEQUENCE_SIZE 1
#define PACKET_TIMESTAMP_SIZE 8
#define PACKET_HEADER_SIZE 32
#define MAX_PAYLOAD_SIZE 512
#define MAX_PACKET_SIZE PACKET_HEADER_SIZE + MAX_PAYLOAD_SIZE

/* FUNCTION PROTOTYPES */

void log_message(char* message);
void debug_log_message(char* message);
void sigusr1_handler(int);
void stream_data(char*, int, char*, int, int, int);
void *get_in_addr(struct sockaddr *sa);
void pack_payload(unsigned char *packet, unsigned char *payload, int frame_number, int frame_size, int payload_size, int payload_offset);

/* GLOBAL VARIABLES */
char message_to_log[255];
int keep_streaming;
FILE *fp1, *fp2;

/* MAIN FUNCTION
 * argv[1] = SERVER_IP [ROUTER_IP]
 */
int main(int argc, char *argv[])
{
    /* LOGGING */
    if ((fp1 = fopen(LOG_FILENAME, "ab+")) == NULL) {
        perror("listener: did not open the log file successfully:");
        return 0;
    }       
    if ((fp2 = fopen(DEBUGLOG_FILENAME, "ab+")) == NULL) {
        perror("listener: did not open the debug_log file successfully:");
        return 0;
    }           
    log_message("started");

    /* INTER PROCESS SIGNALS */
    int streaming = 0;
    int child_status;
    int pid;


    /* UDP LISTENER SETUP */
    // vars
    int fd_socket, return_value, n_bytes;
    int requested_number_of_bytes, delay_between_reads, read_attempts;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;    
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];        
    char buf[MAXBUFLEN]; 
    char source_ip[100];    
    // begin setup
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // set to AF_INET to force IPv4 // AF_UNSPEC
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    // retrieve *servinfo according to the SERVER IP:PORT
    // probably unnecessary but more rigorous
    if (return_value = getaddrinfo(argv[1], LISTEN_PORT, &hints, &servinfo) != 0) {
        fprintf(stderr, "Error in getaddrinfo().\n   ... error_text:%s\n", gai_strerror(return_value));
        return EXIT_FAILURE;
    }
    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((fd_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }
        if (bind(fd_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(fd_socket);
            perror("listener: bind");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }
    freeaddrinfo(servinfo); // clean up linked list

    /* BEGIN LISTENING */
    while (1)
    {

        // receive a packet (blocking)
        addr_len = sizeof their_addr;
        if ((n_bytes = recvfrom(fd_socket, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }               
        buf[n_bytes] = '\0';        
        strcpy(source_ip, inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));        
        sprintf(message_to_log, "received %d bytes from %s as '%s'", n_bytes, source_ip, buf);
        log_message(message_to_log);

        // execute requested command
        if (strncmp("kill", buf, 4) == 0) { 
            // Kill Command
            // Stops the listener.            
            // since the code waits on forks, there should be no children alive at this point
            log_message("Received KILL command.");
            if (!streaming) break;
            else log_message("Cannot break while streaming.");
        } else if (strncmp("play", buf, 4) == 0) {             
            // Play Command
            if (!streaming)
            {
                // Start streaming to the caller's IP Address (blocking by 'streaming' flag)
                sprintf(message_to_log, "Received PLAY command from '%s'", source_ip);
                log_message(message_to_log);
                streaming = 1; //todo: if streaming errors out, this flag does not get reset!
                pid = fork();
                if (pid > 0) { // parent process - keeps on listening
                } else if (pid == 0) { // child process - kicks off the stream
                    stream_data(source_ip, 1, " ", BYTES_PER_FRAME * FRAMES_PER_REQUEST, BOX_LAG_TIME_US, MAX_LOOPS);
                    exit(3); // should never reach this point
                } else {
                    log_message("error trying to create a child");
                    exit(4); // error trying to create a child.
                }
            }
        } else if (strncmp("stop", buf, 4) == 0) {
            // Stop Command
            if (streaming)
            {
                // When streaming, signal the child process
                log_message("Received STOP command."); // log to file
                streaming = 0;            
                kill (pid, SIGUSR1); // sending the stop signal
                wait(&child_status); // wait for the kid to die
                if (WIFEXITED(child_status)) {
                    sprintf(message_to_log, "streaming stopped- child returned '%d'", WEXITSTATUS(child_status));
                    log_message(message_to_log);                    
                }
            }
        } else if (strncmp("rand", buf, 4) == 0) {
            // Random Command
            // Do something randomly            
            sprintf(message_to_log, "Received RANDOM command.");
            log_message(message_to_log);         
        } else {
            // MeXBox Command
            // Set up connection to Box and stream result
            // todo: NEED MORE RIGOROUS ERROR CHECKING FOR FORMAT HERE

            char tmp_buf[MAXBUFLEN]; 
            strcpy(tmp_buf, buf);

            char cmd[32];
            strcpy(cmd, strtok(tmp_buf, "|"));
            requested_number_of_bytes = atoi(strtok(NULL, "|"));
            delay_between_reads = atoi(strtok(NULL, "|"));
            read_attempts = atoi(strtok(NULL, "|"));

            sprintf(message_to_log, "Received a custom set of commands: {%s}{%d}{%d}{%d}", cmd, requested_number_of_bytes, delay_between_reads, read_attempts);
            log_message(message_to_log);   
            stream_data(source_ip, 0, cmd, requested_number_of_bytes, delay_between_reads, read_attempts);
            sprintf(message_to_log, "Successfully transmitted response.");
            log_message(message_to_log);   
        }    

    }

    /* CLEAN UP */
    fclose(fp1);
    fclose(fp2);
    close(fd_socket);        
    return EXIT_SUCCESS;
}


/* ------------------------------------------------------
 *                  FUNCTION DEFINITIONS
 * ------------------------------------------------------
 */

// posts a message to the pre-defined log file
void log_message(char* message)
{ 
    //time_t currTime = time(NULL);
    //fprintf(fp1, "%slistener: %s:\n", ctime(&currTime), message);
    fprintf(fp1, "listener: %s:\n", message);
    debug_log_message(message);
}

// posts a message to the pre-defined debug log file
void debug_log_message(char* message)
{
    fprintf(fp2, "listener: %s:\n", message);
}

// Gets IP whether in IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) 
        { return &(((struct sockaddr_in*)sa)->sin_addr); }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// sigusr1 handler
void sigusr1_handler(int sig)
{
    if (sig == SIGUSR1)
        keep_streaming = 0;
}

// streams data
void stream_data(char *dest_ip, int stream_flag, char *cmd, int expected_bytes, int delay_between_reads, int read_attempts)
{   /* -------------------------------------------
     * Child process: Interracts with MexBox
     * Quits when signaled to stop by the parent
     * Start by configuring UDP talker settings 
     * dest_ip = destination IP address
     * stream_flag = will we be streaming the command perpetually?
     * cmd = the string of commands to send to the MexBox
     * expected_bytes = the total number of bytes to read from the box
     * delay_between_reads = time in microseconds of the delay between box reads
     * read_attempts = the number of attempts at reach the expected_bytes
     * -------------------------------------------
     */

    // streaming doesn't support cmd != " "
    if ( stream_flag && strcmp(cmd, " ") != 0 ) {
        sprintf(message_to_log, "ERROR: %d:Tried to stream '%s'. Should not be streaming any value other than ' ' (space).", strcmp(cmd, " "), cmd);
        log_message(message_to_log);
        exit(3);
    }

    // if we're streaming continuously, set up the signal handler
    if ( stream_flag )
        signal( SIGUSR1, sigusr1_handler );

    // UDP vars    
    int fd_socket, return_value, n_bytes;
    struct addrinfo hints, *servinfo, *p;     
    //
    int flag = 0;    
    int i, j, n_loops; // iterators
    int fd_comport, n_ret_bytes, tot_ret_bytes;
    unsigned int bytes_to_next_frame, bytes_available_to_send;
    unsigned int bytes_to_send;
    unsigned int frames_sent, frame_size;
    unsigned char frame_buffer[BYTES_PER_FRAME * FRAMES_PER_REQUEST + 512]; // 512 is a random margin        
    char report_packet[1024];    
    //unsigned long counter; 
    unsigned int frame_number = 0; // 4 Bytes
    unsigned int payload_size = 512;
    unsigned int payload_offset = 0;
    unsigned char packet[MAX_PACKET_SIZE]; // packet size is 512 B (payload) + 13 B (header) = 524 B

    sprintf(message_to_log, "Parameters:cmd:%s:expected_bytes:%d:read_delay:%d:read_attempts:%d:", cmd, expected_bytes, delay_between_reads, read_attempts);
    log_message(message_to_log);

    // INITIALIZE UDP
    // UDP hints
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // set to AF_INET to force IPv4 // AF_UNSPEC
    hints.ai_socktype = SOCK_DGRAM;
    // retrieve *servinfo according to the SERVER IP:PORT
    // probably unnecessary but more rigorous
    if (return_value = getaddrinfo(dest_ip, DEST_PORT, &hints, &servinfo) != 0) {
        fprintf(stderr, "talker: Error in getaddrinfo(). error_text:%s\n", gai_strerror(return_value));
        exit(1);
    }
    // loop through all results to find an available result that makes a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        // try to open the socket
        if ((fd_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("talker: Socket Opening Error.");
            continue;
        } 
        break; // result found
    }  
    if (p == NULL) {
        fprintf(stderr, "talker: Failed to create a socket.\n");
        exit(2);
    }
    // clean up linked list
    freeaddrinfo(servinfo);

    // ----------------------------------------------------------------------------------------------------------- 
    // SEND MEX BOX DATA 
    // 0. If press play then fork control. 1. Open COM connection. 2. Get data. 3. Stream data. 
    if ((fd_comport = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0) { 
        perror("Connection to MexBox was not successfully made."); 
    } else {
        log_message("MexBox connection made successfully.");

        /* STREAM or send single command*/
        frame_number = 0;
        keep_streaming = 1;
        frame_size = BYTES_PER_FRAME;
        while (keep_streaming) 
        {
            if (!stream_flag) keep_streaming = 0;

            /* Make one REQUEST for FRAMES_PER_REQUEST number of frames */
            write(fd_comport, cmd, strlen(cmd));
            payload_offset = 0; // reset the offset before transmission            
            frames_sent = 0; // keep track of frames already sent: used when streaming frames
            bytes_available_to_send = 0;
            bytes_to_next_frame = 0;
            for (n_loops = 0, tot_ret_bytes = 0; (tot_ret_bytes < expected_bytes) && (n_loops < read_attempts); n_loops++) 
            {

                /* GIVE BOX TIME */
                usleep(delay_between_reads);

                /* RETRIEVE DATA FROM BOX */
                // log results
                //sprintf(message_to_log, "a-{%d}{%d}{tot_ret_bytes:%d}{offset:%d}{available:%d}{to_next:%d}", frame_number, frames_sent, tot_ret_bytes, payload_offset, bytes_available_to_send, bytes_to_next_frame);
                //debug_log_message(message_to_log);
                //debug_log_message("reading data");
                //if (tot_ret_bytes == 0) flag = 1;
                if ((n_ret_bytes = read(fd_comport, frame_buffer + tot_ret_bytes, READ_SIZE)) > 0) 
                    tot_ret_bytes += n_ret_bytes;   


                /* SEND PACKETS - When streaming, send each frame as it becomes available */
                if ( stream_flag ) 
                {   // assumes we are streaming the " " command

                    // if we have a full payload, or enough to finish sending off a frame, then we want to send a packet
                    frames_sent = payload_offset / frame_size;
                    bytes_available_to_send = tot_ret_bytes - payload_offset;
                    bytes_to_next_frame = frame_size * (frames_sent + 1) - payload_offset;                    
                    while ((bytes_available_to_send >= MAX_PAYLOAD_SIZE) || ((bytes_available_to_send > 0) && (bytes_available_to_send >= bytes_to_next_frame)) )
                    {

                        // send packet
                        if (bytes_to_next_frame <= MAX_PAYLOAD_SIZE) { // the while condition ensures we have enough bytes to cover the frame. also assumes the MAX_PAYLOAD_SIZE < FRAME_SIZE
                            payload_size = bytes_to_next_frame;
                        } else {
                            payload_size = MAX_PAYLOAD_SIZE;
                        }
                        pack_payload(packet, frame_buffer, frame_number, frame_size, payload_size, payload_offset);
                        n_bytes = sendto(fd_socket, packet, (payload_size + PACKET_HEADER_SIZE), 0, p->ai_addr, p->ai_addrlen);
                        payload_offset += payload_size;
                        if (bytes_to_next_frame <= MAX_PAYLOAD_SIZE) frame_number++;

                        // refresh results for next cycle
                        frames_sent = payload_offset / frame_size;
                        bytes_available_to_send = tot_ret_bytes - payload_offset;
                        bytes_to_next_frame = frame_size * (frames_sent + 1) - payload_offset;
                        // log results
                        //sprintf(message_to_log, "b-{%d}{%d}{tot_ret_bytes:%d}{offset:%d}{available:%d}{to_next:%d}", frame_number, frames_sent, tot_ret_bytes, payload_offset, bytes_available_to_send, bytes_to_next_frame);
                        //debug_log_message(message_to_log);                                                

                    }
                    //debug_log_message("");
                }
            }

            /* SEND PACKETS - When not streaming, send data entirely after read */
            // can probably package the whole send procedure into its own seperate function later
            if ( !stream_flag ) { // for any other 

                bytes_to_send = tot_ret_bytes; // does not discriminate between frames
                while (bytes_to_send) {
                    if (bytes_to_send >= MAX_PAYLOAD_SIZE){
                        payload_size = MAX_PAYLOAD_SIZE;
                        bytes_to_send -= MAX_PAYLOAD_SIZE;                        
                    } else {
                        payload_size = bytes_to_send;
                        bytes_to_send = 0;
                    }
                    pack_payload(packet, frame_buffer, frame_number, frame_size, payload_size, payload_offset);
                    n_bytes = sendto(fd_socket, packet, (payload_size + PACKET_HEADER_SIZE), 0, p->ai_addr, p->ai_addrlen);
                    payload_offset += payload_size;
                }

            }

            sprintf(message_to_log, "tot_ret_bytes '%d':n_loops '%d'", tot_ret_bytes, n_loops);
            debug_log_message(message_to_log);  
            if (tot_ret_bytes > expected_bytes) {
                // DO SOMETHING HERE TO INDICATE THAT SOMETHING WENT WRONG
                log_message("UNEXPECTED number of bytes returned");
            }            

        }

    }
    // END SEND DATA
    // -----------------------------------------------------------------------------------------------------------

    // Wrap Up
    close(fd_socket);
    if ( stream_flag && strcmp(cmd, " ") != 0 ) { // we didn't fork if we didn't stream the ' ' command
        sprintf(report_packet, "Child Terminating (%d requests made, %d frames sent, or %d packets sent).", frame_number / FRAMES_PER_REQUEST, frame_number, frame_number * PACKETS_PER_FRAME);
        log_message(report_packet);
        exit(0);       
    }
}

void pack_payload(unsigned char *packet, unsigned char *payload, int frame_number, int frame_size, int payload_size, int payload_offset)
{

    unsigned char *packet_pos;
    unsigned char *tmp;
    int transmitted_offset;

    /* HEADER COMPOSITION
     * ------------------
     * 2B ("MX" signature) + 4B (frame_number) + 2B (frame_size)
     * 2B (payload_size) + 2B (payload_offset) + 4B (reserve)
     * 8B (reserve)
     * 8B (timestamp)
     */
    packet_pos = packet;
    // signature
    memcpy(packet_pos, "MX", 2); packet_pos += 2;
    // frame_number
    memcpy(packet_pos, &frame_number, 4); packet_pos += 4;
    // frame_size - USEFUL NOTE ?? EQUIVALENT TO (tot_ret_bytes / FRAMES_PER_REQUEST) ????
    //tmp = &frame_size; // find least significant two bytes
    memcpy(packet_pos, &frame_size+2, 1); packet_pos++;
    memcpy(packet_pos, &frame_size+3, 1); packet_pos++;
    // payload_size
    //tmp = &payload_size; // least significant bytes of unsigned int
    memcpy(packet_pos, &payload_size+2, 1); packet_pos++;
    memcpy(packet_pos, &payload_size+3, 1); packet_pos++;
    // payload_offset
    transmitted_offset = payload_offset % frame_size;
    //tmp = &transmitted_offset; // least significant bytes of unsigned int
    memcpy(packet_pos, &transmitted_offset+2, 1); packet_pos++;
    memcpy(packet_pos, &transmitted_offset+3, 1); packet_pos++;                    
    // 4B reserve
    memset(packet_pos, 0, 4); packet_pos += 4;
    // 8B reserve
    memset(packet_pos, 0, 8); packet_pos += 8;
    // timestamp
    memset(packet_pos, 0, 8); packet_pos += 8; // empty for now
    // payload
    memcpy(packet_pos, payload + payload_offset, payload_size);   

}


/* // SEND ONE FRAME AT A TIME CODE
                    // determine if the next frame is available to send
                    if ( (tot_ret_bytes / frame_size) - frames_sent > 0 ) {                       
                        bytes_to_send = frame_size;
                        while (bytes_to_send){
                            if (bytes_to_send >= MAX_PAYLOAD_SIZE){
                                payload_size = MAX_PAYLOAD_SIZE;
                                bytes_to_send -= MAX_PAYLOAD_SIZE;                        
                            } else {
                                payload_size = bytes_to_send;
                                bytes_to_send = 0;
                            }
                            pack_payload(packet, frame_buffer, frame_number, frame_size, payload_size, payload_offset);
                            n_bytes = sendto(fd_socket, packet, (payload_size + PACKET_HEADER_SIZE), 0, p->ai_addr, p->ai_addrlen);
                            payload_offset += payload_size;                            
                        }
                        //sprintf(message_to_log, "sent frame_number:%d(%d/%d)", frame_number, frames_sent, FRAMES_PER_REQUEST);
                        //debug_log_message(message_to_log);
                        frames_sent++;
                        frame_number++;
                    }
*/
