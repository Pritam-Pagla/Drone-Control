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

const image = document.getElementById('source');

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
  console.log('Throttle: '+a+'    Yaw: '+b+'    Pitch: '+c+'    Roll: '+d)
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
              mapThrottleandsend(LJoyStickBall.y);
              mapYawandsend(LJoyStickBall.x);
              }, false)
   }, false)

   canvasL.addEventListener('touchend', function(e){            // 'touchend' event in LeftCanvas
       e.preventDefault();
       LJoyStickBall.x = LcenterX;
       mapYawandsend(LJoyStickBall.x);
    }, false)

canvasR.addEventListener('touchstart', function(e){         // 'touchstart' event in RightCanvas
       e.preventDefault(); 
       canvasR.addEventListener('touchmove', function(e){
              var touchobj = e.touches[0]; // reference first touch point for this event
              RJoyStickBall.x = touchobj.pageX - (canvasR.width + RJoyStickBall.w);
              RJoyStickBall.y = touchobj.pageY - RJoyStickBall.h;
              mapPitchandsend(RJoyStickBall.y);
              mapRollandsend(RJoyStickBall.x);
              
          }, false)
   }, false)

   canvasR.addEventListener('touchend', function(e){            // 'touchend' event in RightCanvas
       e.preventDefault();
       RJoyStickBall.x = RcenterX;
       RJoyStickBall.y = RcenterY;
       mapPitchandsend(RJoyStickBall.y);
       mapRollandsend(RJoyStickBall.x);
      }, false)

   function sendThrottleData(e) {         // Send Throttle Value via XMLHTTP "GET" Request
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "throttle?throttleVal="+e, true);
    xhttp.send();
  }
  function sendYawData(e) {         // Send Yaw Value via XMLHTTP "GET" Request
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "yaw?yawVal="+e, true);
    xhttp.send();
  }
  function sendPitchData(e) {         // Send Pitch Value via XMLHTTP "GET" Request
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "pitch?pitchVal="+e, true);
    xhttp.send();
  }
  function sendRollData(e) {         // Send Roll Value via XMLHTTP "GET" Request
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "roll?rollVal="+e, true);
    xhttp.send();
  }

  function mapThrottleandsend(e){                     // Map Throttle Value within 0-1023 and Send
    var throttle_Val = ((LcenterY+195) - e)*(1023/390);
    sendThrottleData(throttle_Val);
  }
  function mapYawandsend(e){                     // Map Yaw Value within 0-1023 and Send
    var yaw_Val = (e - LcenterX)*(1023/195);
    sendYawData(yaw_Val);
  }
  function mapPitchandsend(e){                     // Map Pitch Value within 0-1023 and Send
    var pitch_val = (RcenterY - e)*(1023/195);
    sendPitchData(pitch_val);
  }
  function mapRollandsend(e){                     // Map Roll Value within 0-1023 and Send
    var roll_val = (e - Rcenterx)*(1023/195);
    sendPitchData(pitch_val);
  }

   

   document.addEventListener('keydown', function (e) {        // When certain key is pressed down
    if (e.key == 'ArrowRight') {
      LmoveRight();
    } if (e.key == 'ArrowLeft') {
      LmoveLeft();
    } if (e.key == 'ArrowUp') {
      LmoveUp();
    } if (e.key == 'ArrowDown') {
      LmoveDown();
    }
    if(e.key == 'w'){
      RmoveUp();
    }
    if(e.key == 's'){
      RmoveDown();
    }
    if(e.key == 'a'){
      RmoveLeft();
    }
    if(e.key == 'd'){
      RmoveRight();
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
    }
  });

  LeftUpdate();
  RightUpdate();