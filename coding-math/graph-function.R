fun <- function(x) {
  x^2 + 2*x + 1
}
grid(plot(fun,from=-5,to=5,ylim=c(-8,8), col="red"))

abline(v=0,h=0,lty=2)
