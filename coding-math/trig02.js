window.onload = function() {
  var canvas = document.getElementById("canvas"),
      context = canvas.getContext("2d"), //we call all graphics functions on this shit
      width = canvas.width = window.innerWidth,
      height = canvas.height = window.innerHeight;

  var centerY = height * .5;
  var centerX = width * .5;
  var offset = height * .4;
  var speed = 0.01;
  var angle = 0;
  var x = 0;

  var baseRadius = 100;


  render();

  function render() {
    var y = centerY + Math.tan(angle) * offset;
    context.clearRect(0, 0, width, height);

    context.beginPath();
    context.arc(x, y, 10, 0, Math.PI * 2, false);

    context.fill();

    angle += speed;
    x += 0.1;

    requestAnimationFrame(render);
  }
};
