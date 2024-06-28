// estimating model: we collect data. (y,x) => estimate beta
// numeric simulation: we would set some beta. generate data (y,x| beta). estimate, compare with the true beta. => way to examine whether the method works. 
cd "D:\THU\Sophomore\Econometrics\PS4"
clear

log using "2022011545-5.log", replace

clear
// Set number of observations
eststo clear
set obs 1000
// Generate variables
/// y = beta0 + beta1 * x + u.
g id = _n
g x = runiform()
g u = rnormal()
g y = 3*x + u
// Estimate the model using OLS
reg y x
eststo m1 //store the results

// Replicate each observation by 4
expand 4, gen(dupind)

// Estimate the model using OLS and the new sample
reg y x
eststo m2
// Cluster the standard error
reg y x, cluster(id)
eststo m3

// Show all results
esttab m*, se(3)
