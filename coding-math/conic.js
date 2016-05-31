window.onload = function() {
  var canvas = document.getElementById("canvas"),
      context = canvas.getContext("2d"),
      width = canvas.width = window.innerWidth,
      height = canvas.height = window.innerHeight,

      centerX = width / 2,
      centerY = height / 2,
      radius = 200,
      angle = 0,
      speed = 0.1,
      x, y;

  //drawConvexNGon();
  //drawCircleWithArc();

  drawEllipse();

  var minorRadii = 189;
  var majorRadii = 290;

  function drawEllipse() {
    x = centerX + Math.cos(angleInRadians) * minorRadii;
    y = centerY + Math.sin(angleInRadians) * majorRadii;

    context.beginPath();
    context.arc(x, y, 1, 0, Math.PI * 2, false);
    context.fill();
    angleInRadians += speed;
    requestAnimationFrame(drawEllipse);
  }

  //major vertice
  context.beginPath();
  context.moveTo(centerX, centerY - majorRadii);
  context.lineTo(centerX, centerY + majorRadii);
  context.stroke();

  //minor vertice
  context.beginPath();
  context.moveTo(centerX - minorRadii, centerY);
  context.lineTo(centerX + minorRadii, centerY);
  context.stroke();

  //foci up
  var fociLength = Math.sqrt(majorRadii * majorRadii - minorRadii * minorRadii);
  context.beginPath();
  context.moveTo(centerX - minorRadii, centerY);
  context.lineTo(centerX, centerY - fociLength);
  context.stroke();

  //foci down
  context.beginPath();
  context.moveTo(centerX - minorRadii, centerY);
  context.lineTo(centerX, centerY + fociLength);
  context.stroke();

  var angleInRadians = 0;
  var oldX, oldY;
  var numberOfAngles = 8;
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
