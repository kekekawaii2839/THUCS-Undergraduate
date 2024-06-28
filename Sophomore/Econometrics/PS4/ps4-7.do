cd "D:\THU\Sophomore\Econometrics\PS4"
clear

log using "2022011545-7.log", replace

use card, clear

**(a)
gen exper2 = exper * exper
reg lwage educ exper exper2 smsa motheduc, robust

**(b)
reg educ nearc4, robust

**(c)
ivreg lwage (educ = nearc4) exper exper2 smsa motheduc, robust

log close
