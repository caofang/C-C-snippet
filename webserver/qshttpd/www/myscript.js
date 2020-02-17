var myBody = document.getElementById("myBody");
var myCanvas = document.getElementById("myCanvas");
var canvas = myCanvas.getContext("2d");
var screenRatio;

var fps = 20;
var video_interval;
var flip_interval;
var imgRatio;
var img = new Image();
img.src = "/?action=stream";
//img.src = "img/bmw_m6.jpg";
var mjpeg = 1;
var flitFlag=1;


window.setTimeout(function(){video_control("start")},1000);
function video_control(cmd)
{
	if(mjpeg && cmd == "start") 
	{
		myCanvas.width = window.innerWidth; 
		myCanvas.height = window.innerHeight;
		screenRatio = myCanvas.width/myCanvas.height;
		video_interval = setInterval(drawImg,1000/fps);
	}
	if(cmd == "stop") clearInterval(video_interval);
}

window.onload = function()
{

	myCanvas.width = window.innerWidth; 
	myCanvas.height = window.innerHeight;
	screenRatio = myCanvas.width/myCanvas.height;
	if(!mjpeg)drawImg();
}

var i = 0;
var rotateFlag=0;
var flipFlag=0;

window.onresize = function(e)
{
	myCanvas.width = window.innerWidth; 
	myCanvas.height = window.innerHeight;
	screenRatio = myCanvas.width/myCanvas.height;
	if(!mjpeg)drawImg();
}


var dx;
var dy;
var dw;
var dh;
function drawImg()
{
	// console.log("img and canvas",img.height, img.width ,myCanvas.width,myCanvas.height);
	var str="";
	imgRatio = img.width/img.height;
	if(myCanvas.width >= img.width && myCanvas.height >= img.height) {
		dx = myCanvas.width/2 - img.width/2;
		dy = (myCanvas.height - img.height)/2;

		dw = img.width;
		dh = img.height;
		str = "full";
	}
	else 
	{
		// playing with image ratio
		// 1280 x 720
		if(screenRatio > imgRatio)	// wide screen
		{
			// console.log("wide screen");
			dw = myCanvas.height * imgRatio;
			dh = myCanvas.height;
		}
		else if(screenRatio < imgRatio)	// tall screen
		{
			// console.log("tall screen");
			dw = myCanvas.width;
			dh = myCanvas.width / imgRatio; 
		}
		else	// perfect 
		{
			// console.log("fit screen");
			dw = myCanvas.width;
			dh = myCanvas.height;
		}

		if(myCanvas.width > dw) dx = (myCanvas.width - dw)/2;
		else dx = 0;

		if(myCanvas.height > dh) dy = (myCanvas.height - dh)/2;
		else dy =0;
		str = "shrink";
	}

	console.log(str, "imgRatio",imgRatio,img.width,img.height,
		"dw dh",dw,dh, 
		"canvas",myCanvas.width,myCanvas.height,
		"screenRatio", screenRatio);
	canvas.clearRect(0,0,myCanvas.width,myCanvas.height);
	canvas.drawImage(img,0,0,img.width,img.height,dx,dy,dw,dh);
	if(flitFlag) flipImage();
}

function flipImage()
{
	var x = myCanvas.width;
	var y = myCanvas.height;
    canvas.save();
    canvas.translate(x, 0);
	canvas.scale(-1, 1);
    canvas.drawImage(img,0,0,img.width,img.height, dx,dy,dw,dh);
    canvas.restore(); 
}


