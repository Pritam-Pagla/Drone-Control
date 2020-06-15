const char MAIN_page[] PROGMEM = R"=====(<!DOCTYPE html>
<html lang = 'en'>
  <head>
    <meta charset="UTF-8"/>
    <meta name="viewport"
    content="width=950, height=420 initial-scale=1.0"/>
    <meta http-equiv="X-UA-Compatible"
    content="ie=edge"/>
    <title>Drone Remote</title>
    <style>
    body{
      background-color: #333;
      color: 'black';
      display: flex;
      flex-direction: row;
      align-items: center;
      font-family: Arial, Helvetica, sans-serif;
      min-height: 100vh;
      margin:0;
    }
    #canvasL{
      background: #f0f0f0;
      border-radius: 5x
    }
    #canvasM{
      background: #f0f0f0;
      border-radius: 5px
    }
    #canvasR{
      background: #f0f0f0;
      border-radius: 5px
    }
    
    #source{
      display: none;
    }

    </style>
  </head>
  <body>
    <canvas id="canvasL" width="450" height="420"></canvas>
    <canvas id="canvasM" width="50" height="420"></canvas>
    <canvas id="canvasR" width="450" height="420"></canvas>

    <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADIAAAAyCAYAAAAeP4ixAAAHWElEQVRoQ7WZT2xUVRTGv9vptIBAC6ghbtQYEhtD4kLcsJCNUdOtLUldGKOuujH+STQYDcGQKEFWGv8LIQgMqcrG6AZcGEkwxEjShUFJVxAIaEVsC23nmnN7v+mZM/fOvJm2L3m5b968ee/87vedc++747BC2/vA1iqwfR54aA6Y98CvM8DP7wAXVuKRbjlu+iXQXwX+rgLwAKSVfQ7AfNzleDae0y2ANQeA6aXGsSSQIwuxdUsQ3jls3b0brlRC1fsFIO9r+3w8FjA5PzM9jVP79oUbyH4buPEp0NcpUEcgFYkbgOwP7toF19UFHwOVNgvhfVBoTlq1/zs5iZ8OHhQY2ecPx85pB6otkDHgRwc81gVg8+Ag1g8MABK4Cj4cxyCpSLCX9wFAzhFEWrFcaL3H+KlTuHTxYgCaBV6tAPuLwhQG+QbwJQCy3zc6Cud9gCCIPDBYihZSVmLvM+AApQB4/rb3uD07izNjYwFG8qyyIHzLrchF7iRQlUSQ/Z6REZR6eupArCrMB/a8BDQbVWLQ0oaklzYqIq3A/HnuHK5evhy+l60ITFOQr4FN3cC1coQQNTYPD6PL+wBCVSQnqISoov2f6nlCSODcCRRgAJw/fTq0cu8iMFmQCtCzCrglEAQRRe4cHFwECeUq5oiylM4JgdI9rlWgAgIhSoTqFY9/P3s2gMi9uDVTJgvyLeAFoCeCSCsg/Tt2BBBJ+JoiqmIFOxn/13o+WowAPB+qFWG8xy3vMTE+zqSvy48cTBJkDPC9CoAwArZ+2zaUoq0EhoqwQulKpK3D4ENFikEz+NAqGPl8aWICtxbKccOWgmkAOQZUVwGOIA1A3d1YvWVLqF6ijAZJQQTLxF7W1pFeJ0gIOH6W89evXq1ByHfME0X0QwV4UhM2gJyIagiAKCG7PhZVejdsQHnduqAMQcROtvpIcBIIFUgFz3PTEeTm1BRmqtU6EKl6drOq1IEcBTwDZ/C2JZzkS3njxpAnYV4VS6gERgXEFjr4mahMOBe/k2OeF4BwPu481gmvgTRMA4gEzl1D5YCcc5grlxeDVxYJATFoFaANlJ+ZE/qzHLcFcihayiqyKtqLrYUUZWwA0pMzMVHZ2mBT59sF0eNLTREBySmQUogWk8olg17KErme16C29/V9+F1OkQaQj4G/eoEN2j72WCc8y7GoIT0Rxo0IE2ewdSrZ4Cx0Tr1WOSIgDnj0OPBLUOSjjK1SlUuP9FKC5QaS7KFqLb5bcEpeA8oFn7KTBU9VLZv0AeRDU3ItAEd4rQRnwmFMVG+C8SWpNiqH8mvyiIGm4ORamz+JcaRhtHcecB8AVRt8bmTXE0gmGF9vaTGrjAZJWU+rksq1xDDSCLIf2FsG3rA5oOdYnGdpCNqKd6S9wmzX2EyrRBCriv6siwGn8s1g5oEB966qVtpCdQNfnHfJ97RUmDTGPbXgoBcY4htfLW9SMDmwZhVLwR1yeyMIA9dKMLH1NN6CMEesvawyNndyMNZarfKDMG6PAmHgKTUEQMptmCzGXU8LuASkl4G0xZg31mbMn1RBKGKrGsjbRhGrglZDAARG20rnCKsXYagKxxjaTavRLH9ald262e+b8QVK50eYEMag+a5OACrC/ODNdJ7oRTkNY1XJ2Y0lu1W1qgN53YBIwKxSErROcOaHQISXKpXs4b1dDY4pGA2iS3QKqGCSk+WMewX4vgw8oUusVYMANj/0OGJB7JJparmUABakndyIJI8LyL0OmLCLDFSCCW4hqIiWVye8Hlf0QJmrZlqhopWKz5b3ktCpLwGeuWBLbQ6EakjLB+tFbFpLW4zzsVw1E5g2LRVYaiCjCRDayZZcViyriLZWqhRTFa0IqxnbTiDqQF6MCa8rlAaRoDkl4RjCRNdVy8KkVOFfDbSS/ruhnSqlrr1WAe4KDhkCSn3AnM0LW3L1QGhXLQhhyzBzhYrYfOnUTjo/6jr1WWUvXaV0kmtbtQJJlWJrL6rToRK1/KgDGQE+KwHP6+TW8yqqkRrV9XyLAHqU1xbT1mq3OlngMtB3BLhhbY6dURUNkJrt6sEwlyMaJGWvpahgbZUCec4DX4htUvmhR/Rc1UpVL63IcgDIPXqBtYeB/3i/hpXGYbVCycBTtkotGmsIm/TLBZBSo0ERXqRhNDEninbCaO3FgXG5g89BZEGGgI0OuL5SgSzlvm39rRDHFlkremQpD13u33YBLxwDPk/dt+lfb0PAFQfcXTSg1H8ZzX4rM+6imwe+OgE8k7u+KYj8aCfwhwceaPbAm0WjyVy3tvXv36oAe5pd1hIk2ux+B1xM3WiydRCFrujPXNUP9HyysMbXdCsEwjukqtlyVYRNiTCL/C3Nn7UFEtV5zQHv6eeKKi27LNOfawDcYb5zwMPHgd9aqaC/bxuEPx4CvnPAU/Zh/8R13mZBSPCZvHi5AhxoB6BjRexDhoDVDpjq5OH8zQBQ2r2wqN/x1rEiuScOA9s9cNIBKdvLa/GFbuDpo8D5jqNO/PB/ioZ2+ax3loAAAAAASUVORK5CYII=" alt="" id="source"/>
    <script>
    const canvasL = document.getElementById('canvasL');       // Object for left canvas
const Lctx = canvasL.getContext('2d');

const canvasM = document.getElementById('canvasM');       // Object for Middle canvas
const Mctx = canvasM.getContext('2d');

const canvasR = document.getElementById('canvasR');       // Object for Right canvas
const Rctx = canvasR.getContext('2d');

const LcenterX = (canvasL.width / 2);    // Marking centre for left Joystick
const LcenterY = (canvasL.height / 2);
const RcenterX = (canvasR.width / 2);    // Marking centre for Right Joystick
const RcenterY = (canvasR.height / 2);
const McenterX = (canvasM.width / 2);    // Marking centre for Middle Portion
const McenterY = (canvasM.height / 2);


var Tsocket = new WebSocket('ws://' + window.location.hostname + ':9001/');
var Ysocket = new WebSocket('ws://' + window.location.hostname + ':9002/');
var Psocket = new WebSocket('ws://' + window.location.hostname + ':9003/');
var Rsocket = new WebSocket('ws://' + window.location.hostname + ':9004/');

const image = document.getElementById('source');

var throttle_Val = 0;
var yaw_Val = 0;
var pitch_Val = 0;
var roll_Val = 0;

const throttle = "t";
const yaw = "y";
const pitch = "p";
const roll = "r";

const LJoyStickBall = {         // defining left joystick as an object
  w: 60,
  h: 60,
  x: LcenterX,
  y: LcenterY+195,
  speed: 1,
  dx: 0,
  dy: 0
};
const RJoyStickBall = {         // defining right joystick as an object
  w: 60,
  h: 60,
  x: RcenterX,
  y: RcenterY,
  speed: 1,
  dx: 0,
  dy: 0
};

function drawLeftCenterBall(){      //Drawing the Left Joystick ball
  Lctx.drawImage(image, LJoyStickBall.x-30, LJoyStickBall.y-30, LJoyStickBall.w, LJoyStickBall.h);
}
function drawRightCenterBall(){      //Drawing the Right Joystick ball
Rctx.drawImage(image, RJoyStickBall.x-30, RJoyStickBall.y-30, RJoyStickBall.w, RJoyStickBall.h);
}

function LnewPos() {                    // changing position for keyboard activity
  LJoyStickBall.x += LJoyStickBall.dx;
  LJoyStickBall.y += LJoyStickBall.dy;

  LdetectBoundary();
}

function RnewPos() {                    // changing position for keyboard activity
  RJoyStickBall.x += RJoyStickBall.dx;
  RJoyStickBall.y += RJoyStickBall.dy;

  RdetectBoundary();
}

function LdetectBoundary(){             // defining the boundary for the LeftJoystickCenterBall
  // Left side
  if (LJoyStickBall.x < LcenterX-195) {
    LJoyStickBall.x = LcenterX-195;
  }

  // Right side
  if (LJoyStickBall.x > LcenterX+195) {
    LJoyStickBall.x = LcenterX+195;
  }

  // Top side
  if (LJoyStickBall.y < LcenterY-195) {
    LJoyStickBall.y = LcenterY-195;
  }

  // Bottom side
  if (LJoyStickBall.y > LcenterY+195) {
    LJoyStickBall.y = LcenterY+195;
  }
}

function RdetectBoundary(){             // defining the boundary for the LeftJoystickCenterBall
  // Left side
  if (RJoyStickBall.x < RcenterX-195) {
    RJoyStickBall.x = RcenterX-195;
  }

  // Right side
  if (RJoyStickBall.x > RcenterX+195) {
    RJoyStickBall.x = RcenterX+195;
  }

  // Top side
  if (RJoyStickBall.y < RcenterY-195) {
    RJoyStickBall.y = RcenterY-195;
  }

  // Bottom side
  if (RJoyStickBall.y > RcenterY+195) {
    RJoyStickBall.y = RcenterY+195;
  }
}


function drawDesigns(){               // 4 Convrntric circles and 2 crossed st lines for better interface
  Lctx.beginPath();
  Lctx.lineWidth = 2.5;
  Lctx.moveTo(LcenterX, LcenterY-195);    // Crossing lines on left
  Lctx.lineTo(LcenterX, LcenterY+195);
  Lctx.moveTo(LcenterX-195, LcenterY);
  Lctx.lineTo(LcenterX+195, LcenterY);
  Lctx.arc(LcenterX, LcenterY, 195, 0, Math.PI * 2);   //Concentric circles on Left
  Lctx.arc(LcenterX, LcenterY, 150, 0, Math.PI * 2);
  Lctx.arc(LcenterX, LcenterY, 100, 0, Math.PI * 2);
  Lctx.arc(LcenterX, LcenterY, 50, 0, Math.PI * 2);
  Lctx.stroke();

  Rctx.beginPath();
  Rctx.lineWidth = 2.5;
  Rctx.moveTo(RcenterX, RcenterY-195);    // Crossing lines on Right
  Rctx.lineTo(RcenterX, RcenterY+195);
  Rctx.moveTo(RcenterX-195, RcenterY);
  Rctx.lineTo(RcenterX+195, RcenterY);
  Rctx.arc(RcenterX, RcenterY, 195, 0, Math.PI * 2);   //Concentric circles on Right
  Rctx.arc(RcenterX, RcenterY, 150, 0, Math.PI * 2);
  Rctx.arc(RcenterX, RcenterY, 100, 0, Math.PI * 2);
  Rctx.arc(RcenterX, RcenterY, 50, 0, Math.PI * 2);
  Rctx.stroke();
}
function clearScreen(){             // Clearing the LeftCanvas and RightCanvas on every loop of the Animation
  Lctx.clearRect(0, 0, canvasL.width, canvasL.height);
  Rctx.clearRect(0, 0, canvasR.width, canvasR.height);
}

function ConsoleOUT(a,b,c,d){
   throttle_Val = (405-a);
   yaw_Val = (b-225);
   pitch_Val = (210-c);
   roll_Val = (d-225);
  console.log('Throttle: '+throttle_Val+'    Yaw: '+yaw_Val+'    Pitch: '+pitch_Val+'    Roll: '+roll_Val);
}

function LeftUpdate(){
  clearScreen();                                //Left Joystick
  drawDesigns();
  drawLeftCenterBall();
  drawRightCenterBall();
  LnewPos();
  RnewPos();
  ConsoleOUT(LJoyStickBall.y,LJoyStickBall.x,RJoyStickBall.y,RJoyStickBall.x);
  requestAnimationFrame(LeftUpdate);
  
}
function RightUpdate(){                                 //Right Joystick
  clearScreen();
  drawDesigns();
  drawLeftCenterBall();
  drawRightCenterBall();
  LnewPos();
  RnewPos();
  ConsoleOUT(LJoyStickBall.y,LJoyStickBall.x,RJoyStickBall.y,RJoyStickBall.x);
  requestAnimationFrame(RightUpdate);
}

function LmoveUp() {                          // For KeyboardActivity 
  LJoyStickBall.dy = -LJoyStickBall.speed;
}

function LmoveDown() {
  LJoyStickBall.dy = LJoyStickBall.speed;
}

function LmoveRight() {
  LJoyStickBall.dx = LJoyStickBall.speed;
}

function LmoveLeft() {
  LJoyStickBall.dx = -LJoyStickBall.speed;
}
function RmoveUp() {
  RJoyStickBall.dy = -RJoyStickBall.speed;
}

function RmoveDown() {
  RJoyStickBall.dy = RJoyStickBall.speed;
}

function RmoveRight() {
  RJoyStickBall.dx = RJoyStickBall.speed;
}

function RmoveLeft() {
  RJoyStickBall.dx = -RJoyStickBall.speed;
}





canvasL.addEventListener('touchstart', function(e){         // 'touchstart' event in LeftCanvas
       e.preventDefault();    
       canvasL.addEventListener('touchmove', function(e){
              var touchobj = e.touches[0]; // reference first touch point for this event
              LJoyStickBall.x = touchobj.pageX;
              LJoyStickBall.y = touchobj.pageY;
              sendData(throttle,405-LJoyStickBall.y);
              sendData(yaw,LJoyStickBall.x-225);
              }, false)
   }, false)

   canvasL.addEventListener('touchend', function(e){            // 'touchend' event in LeftCanvas
       e.preventDefault();
       LJoyStickBall.x = LcenterX;
       sendData(yaw,0);
    }, false)

canvasR.addEventListener('touchstart', function(e){         // 'touchstart' event in RightCanvas
       e.preventDefault(); 
       canvasR.addEventListener('touchmove', function(e){
              var touchobj = e.touches[0]; // reference first touch point for this event
              RJoyStickBall.x = touchobj.pageX - (canvasR.width + RJoyStickBall.w);
              RJoyStickBall.y = touchobj.pageY - RJoyStickBall.h;
              sendData(pitch,210-RJoyStickBall.y);
              sendData(roll,RJoyStickBall.x-225);
              
          }, false)
   }, false)

   canvasR.addEventListener('touchend', function(e){            // 'touchend' event in RightCanvas
       e.preventDefault();
       RJoyStickBall.x = RcenterX;
       RJoyStickBall.y = RcenterY;
       sendData(pitch,0);
       sendData(roll,0);
      }, false)



  function sendData(a,b){

    if(a == throttle){
      Tsocket.send(b);
    }
    if(a == yaw){
      Ysocket.send(b);
    }
    if(a == roll){
      Rsocket.send(b);
    }
    if(a == pitch){
      Psocket.send(b);
    }
    
    // switch(a){


    //   case throttle:
    //     Tsocket.send(b);
    //     break;
    //   case yaw:
    //     Ysocket.send(b);
    //     break;
    //   case roll:
    //       Rsocket.send(b);
    //       break;
    //   case pitch:
    //       Psocket.send(b);
    //       break;
    //   default:
    //     console.log('Interruption Occured.')
    // }
  }



  document.addEventListener('keydown', function (e) {        // When certain key is pressed down
    if (e.key == 'ArrowRight') {
      LmoveRight();
      sendData(yaw,LJoyStickBall.x-225);
    } if (e.key == 'ArrowLeft') {
      LmoveLeft();
      sendData(yaw,LJoyStickBall.x-225);
    } if (e.key == 'ArrowUp') {
      LmoveUp();
      sendData(throttle,405-LJoyStickBall.y);
    } if (e.key == 'ArrowDown') {
      LmoveDown();
      sendData(throttle,405-LJoyStickBall.y);
    }
    if(e.key == 'w'){
      RmoveUp();
      sendData(pitch,210-RJoyStickBall.y);
    }
    if(e.key == 's'){
      RmoveDown();
      sendData(pitch,210-RJoyStickBall.y);
    }
    if(e.key == 'a'){
      RmoveLeft();
      sendData(roll,RJoyStickBall.x-225);
    }
    if(e.key == 'd'){
      RmoveRight();
      sendData(roll,RJoyStickBall.x-225);
    }
  });
   document.addEventListener('keyup', function (e) {        // When certain key is released 
    if (
      e.key == 'ArrowLeft' ||
      e.key == 'ArrowRight' ||
      e.key == 'ArrowUp' ||
      e.key == 'ArrowDown' ||
      e.key == 'w' ||
      e.key == 's' ||
      e.key == 'a' ||
      e.key == 'd'
    ) {
      LJoyStickBall.dx = 0;
      LJoyStickBall.dy = 0;
      RJoyStickBall.dx = 0;
      RJoyStickBall.dy = 0;
      LJoyStickBall.x = LcenterX;
      RJoyStickBall.x = RcenterX;
      RJoyStickBall.y = RcenterY;
      sendData(yaw,0);
      sendData(pitch,0);
      sendData(roll,0);
    }
  });

  LeftUpdate();
  RightUpdate();
    </script>
  </body>
</html>

)=====";
