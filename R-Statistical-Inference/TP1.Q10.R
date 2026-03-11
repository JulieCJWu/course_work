# MATH682 TP1
# Question 10
# Date: 230925
# Author: Julie Chao-Jung Wu (wu.chaojung@gmail.com)


cdfX = function (x){
  if(x < 0){
    Fx = 0
  }else if(x < 3/2){
    Fx = (2/9) * (x^2)
  }else if(x <= 3){
    Fx = (4/3) * x - (2/9) * (x^2) - 1
  }else{
    Fx = 1    
  }
  return(Fx)
}


pIntX = function(a,b){
  upper_bound = max(a,b) / 10000 
  lower_bound = min(a,b) / 10000
  Pab = cdfX(upper_bound) - cdfX(lower_bound)
  return(Pab)
}


expR = function(z){
  if(z<0){
    message = "Negative prices not allowed"
    print(message)
  }else{
  revenue = z * 15000
  return(revenue)
  }
}


expR(2.05)
expR(0)
expR(-2.05)

pIntX(12000,18000)
pIntX(18000,12000)
pIntX(180000,120000)



cdfX(1.8)
cdfX(1.2)

cdfX(-1)
cdfX(3)
cdfX(1.8) - cdfX(1.2)