cd "D:\THU\Sophomore\Econometrics\PS4"
clear

log using "2022011545-4.log", replace

use gpa, clear
// estimate the model using OLS
reg colgpa hsgpa act skipped pc
// calculate the residual
predict uhat, residual
g uhat2 = uhat^2

// FWLS: estimate weight
g loguh2 = log(uhat2)
reg loguh2 hsgpa act skipped pc
predict g
g h = exp(g)
g w = 1/h
// Method 1: using weight command
reg colgpa hsgpa act skipped pc [aweight = w]
eststo m1 //this command store the reg results
reg colgpa hsgpa act skipped pc [aweight = w], robust
eststo m2
// Method 2: transform the equation
foreach i of varlist colgpa hsgpa act skipped pc{
	g `i'_f = `i' / sqrt(h)
}
g con_f = 1/sqrt(h)
reg *_f, nocons
eststo m3
reg *_f, nocons vce(robust)
eststo m4

// robust standard error of the OLS estimator
reg colgpa hsgpa act skipped pc, vce(robust)
eststo m5

// show all regression results
esttab m*, se



