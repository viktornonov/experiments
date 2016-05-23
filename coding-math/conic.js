window.onload = function() {
  var canvas = document.getElementById("canvas"),
      context = canvas.getContext("2d"),
      width = canvas.width = window.innerWidth,
      height = canvas.height = window.innerHeight,

      centerX = width / 2,
      centerY = height / 2,
      radius = 200,
      angle = 0,
      speed = 0.01,
      x, y;

  drawConvexNGon();
  drawCircleWithArc();

  var angleInRadians = 0;
  var oldX, oldY; 
  var numberOfAngles = 8;
  var minorRadii = 30;
  var majorRadii = 50;
  function drawConvexNGon() {
    x = centerX + Math.cos(angleInRadians) * minorRadii;
    y = centerY + Math.sin(angleInRadians) * majorRadii;
    context.beginPath();
    context.strokeStyle = 'black';
    context.moveTo(x, y);
    context.lineTo(oldX, oldY);
    context.stroke();
    oldX = x;
    oldY = y;
    angleInRadians += (2*Math.PI) / numberOfAngles; //speed;
    requestAnimationFrame(drawConvexNGon);
  }

  function drawCircleWithArc() {
    //context.clearRect(0, 0, width, height);
    x = centerX + Math.cos(angle) * radius;
    y = centerY + Math.sin(angle) * radius;
    context.beginPath();
    context.arc(x, y, 10, 0, Math.PI * 2, false);
    context.fill();
    angle += speed;
    requestAnimationFrame(drawCircleWithArc);
  }

  //TODO[VN] optimize drawing a circle
  //TODO[VN] lissajous curves
}
