
//recursion clasica
function fact(n) {
  if (n == 0)
    return 1 ;
  else
    return n * fact(n-1) ;
}

//recursion de cola
function fact(n) {
  return tail_fact(n,1) ;
}
 
function tail_fact(n,a) {
  if (n == 0)
    return a ;
  else
    return tail_fact(n-1,n*a) ;
}