window.onload = function() {
  var canvas = document.getElementById("canvas"),
      context = canvas.getContext("2d"), //we call all graphics functions on this shit
      width = canvas.width = window.innerWidth,
      height = canvas.height = window.innerHeight;

  context.translate(0, height / 2);
  context.scale(1, -1);
  //context.fillRect(0, 0, width, height);
  //drawRandomLines(context, width, height);
  for(var angle = 0; angle < 2 * Math.PI; angle += .01) {
    console.log(Math.sin(angle));

    var x = angle * 200;
    var y = Math.sin(angle) * 200;

    var y_cos = Math.cos(angle) * 200;

    context.fillRect(x, y, 1, 1);; //draw square with 5 by 5 (simulating pixel)
    context.fillRect(x, y_cos, 1, 1);; //draw square with 5 by 5 (simulating pixel)
  }
};

var drawRandomLines = function(context, width, height) {
  for(var i = 0; i < 100; i += 1) {
    context.beginPath();
    context.moveTo(Math.random() * width, Math.random() * height);
    context.lineTo(Math.random() * width, Math.random() * height);
    context.stroke();
  }
}

