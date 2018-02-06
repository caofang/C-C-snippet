/* ------------------------------ 
     * SEND DATA 
     */
    /* 0. If press play then fork control. 1. Open COM connection. 2. Get data. 3. Stream data. */
    if ((fd_comport = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0)
        { perror("Connection to MexBox was not successfully made."); }
    else
    {
        // top-level loop runs as long as we are 'playing'
        // within, receive a frame, package and send it in 4 packets.

        frame_number = 0;
        while(1 && frame_number < 10) // as long as we want to continue sending packets. remove the second condition and replace with a CONTROL condition from another UDP port
        {

            send_position = 0;
            frame_sequence = 0;
            write(fd_comport, " ", 1);
            for(send_position = 0, n_loops = 0; send_position < 4096 && n_loops < 8; n_loops++) // each frame has 32*64*2 = 4096 bytes. finished sending frame at send_position = 4096. twice as many loops as expected
            {

                // request 1 KB of data. May get less sometimes??
                ret_bytes = read(fd_comport, frame_buffer+send_position, 1024);
                // usleep(?);
                if (ret_bytes > 0) { send_position += ret_bytes; }

                // can I improve this section? mmaybe by making packet length more flexible?
                // does the mexbox stop once it sends a single frame from the space command? or is there a bit of overflow?
                for (i = 0; i < 8; i++)
                {
                    if (send_position >= 512*(i + 1) && frame_sequence == i) // we have enough bytes and are ready to send the next frame partial
                    {
                        // add frame_sequence to the packet, copy packet contents
                        memcpy(packet, &frame_number, 4); // frame_number is 4 B (sizeof (unsigned int))
                        memcpy(packet+4, &frame_sequence, 1); // frame_sequence is 1 B (sizeof (unsigned char))
                        //memcpy(packet+5, ); // time_stamp is 8 B (sizeof (datetime))
                        memset(packet+5, 0, 8); // for now send an empty time_stamp                       
                        memcpy(packet+13, frame_buffer + 512*frame_sequence, 512); // data is 512 B (an eigth of a frame of sensels)

                        // wael todo - need to make sure that n_bytes = 524
                        // if not, then should we just move on to the next frame?
                        n_bytes = sendto(fd_socket, packet, 524, 0, p->ai_addr, p->ai_addrlen));                
                        frame_sequence++;
                    }
                }
            }
            frame_number += 1; // frame_number increments by the number of batched frames received
        }

    }