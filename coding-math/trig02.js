window.onload = function() {
  var canvas = document.getElementById("canvas"),
      context = canvas.getContext("2d"), //we call all graphics functions on this shit
      width = canvas.width = window.innerWidth,
      height = canvas.height = window.innerHeight;

  var centerY = height * .5;
  var centerX = width * .5;
  var offset = height * .4;
  var speed = 0.05;
  var angle = 0;
  var x = 0;

  var baseRadius = 0;
  var baseAlpha;

  bounceBallWithSin();

  function bounceBallWithSin() {
    var y = centerY;
    var x = centerX;
    var magnification = 50;
    context.clearRect(0, 0, width, height);

    baseRadius = Math.abs(Math.sin(angle)) * magnification;
    baseAlpha = Math.abs(Math.sin(angle));
    context.fillStyle = "rgba(0,0,0, " + baseAlpha + ")";
    context.beginPath();
    context.arc(x, y, baseRadius, 0, 2 * Math.PI, false);
    context.fill();

    angle += speed;

    requestAnimationFrame(bounceBallWithSin);
  }

  function bounceBallWithTangent() {
    var y = centerY;
    var x = centerX;
    var magnification = 50;
    context.clearRect(0, 0, width, height);

    baseRadius = Math.abs(Math.tan(angle)) * magnification;
    context.beginPath();
    context.arc(x, y, baseRadius, 0, Math.PI * 2, false);
    context.fill();

    angle += speed;

    requestAnimationFrame(bounceBallWithTangent);
  }

  function bounceBall() {
    var y = centerY + Math.sin(angle) * offset;
    var x = centerX;
    context.clearRect(0, 0, width, height);

    context.beginPath();
    context.arc(x, y, 10, 0, Math.PI * 2, false);
    context.fill();

    angle += speed;

    requestAnimationFrame(bounceBall);
  }

  function goInCircleWithSinAndCos() {
    var y = centerY + Math.sin(angle) * offset;
    var x = centerX + Math.cos(angle) * offset;
    context.clearRect(0, 0, width, height);

    context.beginPath();
    context.arc(x, y, 10, 0, Math.PI * 2, false);
    context.fill();

    angle += speed;

    requestAnimationFrame(goInCircleWithSinAndCos);
  }
};
