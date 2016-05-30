window.onload = function() {
  var canvas = document.getElementById("canvas"),
      context = canvas.getContext("2d"), //we call all graphics functions on this shit
      width = canvas.width = window.innerWidth,
      height = canvas.height = window.innerHeight;

  var centerY = height * .5;
  var centerX = width * .5;
  var offset = height * .4;
  var speedX = 0.03;
  var speedY = 0.3;
  var angleX = [];
  for(var i = 0; i < 10; i++) {
    angleX.push(Math.random() * 10);
  }
  var angleY = [];
  for(var i = 0; i < 10; i++) {
    angleY.push(Math.random() * 10);
  }

  var x = 0;

  var ratioA = [];
  for(var i = 0; i < 10; i++) {
    ratioA.push(Math.random() * 0.1);
  }

  var ratioB = [];
  for(var i = 0; i < 10; i++) {
    ratioB.push(Math.random() * 0.1);
  }

  drawLissajousCurve();

  function drawLissajousCurve() {
    context.clearRect(0, 0, width, height);
    for(var i = 0; i < 10; i++) {
      var x = centerX + Math.sin(angleX[i]) * offset;
      var y = centerY + Math.cos(angleY[i]) * offset;

      drawDot(x, y);

      angleX[i] += ratioA[i];
      angleY[i] += ratioB[i];
    }

    requestAnimationFrame(drawLissajousCurve);
  }

  function drawDot(x, y) {
    context.beginPath();
    context.arc(x, y, 5, 0, 2 * Math.PI, false);
    context.fill();
  };
};
