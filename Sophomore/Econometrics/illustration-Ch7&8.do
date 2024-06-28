* This file illustrates the use of dummy variable, vce options, and WLS.
* Date: 2024/05/04

cd "/Users/yingjiefeng/Dropbox/Classes-Tsinghua/IntroMetrics1/data"
use wage1, clear

********************************
* Generate dummy variables
* 0: exper <= 17; 1: exper > 17
gen mexper=(exper>17)         /* put a condition in () */
tab mexper

***********************************
* For discrete varables, use tab to generate dummies
tab numdep
tab numdep, gen(dum_dep)

*************************************
* regression with all these dummies
reg lwage educ dum_dep*

* factor variable
help factor variable
reg wage i.numdep    /* add dummies corresponding to numdep */
reg wage i.numdep c.exper#i.numdep    /* add dummies, and interact them with the continuous varialbe exp */
reg wage i.numdep##c.exper            /* more concise syntax, the same as the 2nd one */


*****************************
* Chow test
use beauty.dta, clear
* Pooled regression
reg lwage belavg abvavg educ exper expersq
scalar ssr_p=e(rss)
scalar n=e(N)
* Unrestricted regression: two separate regression for males and females respectively
reg lwage belavg abvavg educ exper expersq if female==1
scalar ssr_f=e(rss)
reg lwage belavg abvavg educ exper expersq if female==0
scalar ssr_m=e(rss)
* F stat
scalar F=(ssr_p-(ssr_m+ssr_f))/6/((ssr_m+ssr_f)/(n-12))
di F
di Ftail(6, n-12, F)

* Check this
reg lwage i.female##i.belavg i.female##i.abvavg i.female##c.educ i.female##c.exper i.female##c.expersq
di e(rss)
di ssr_f+ssr_m

*********************************
* robust standard errors
* homoskedasticity s.e. (the following two are the same)
reg wage educ
reg wage educ, vce(ols)
* heterskedasticity-robust s.e. (the following two are the same)
reg wage educ, vce(robust)
reg wage educ, robust

* Note that there are other heterskedasticity-robust s.e. (not required)
* The following two use formulas different from the one covered in class
reg wage educ, vce(hc2)
reg wage educ, vce(hc3)

* There are also other options for vce();
* A very useful and important one is cluster s.e. allowing for within-cluster correlation. We will discuss it later.


***************************************
* weights in STATA
help weights

webuse byssin, clear
* OLS without any weights
reg prob workplace smokes
* WLS: use pop as (analytic) weights (so the error variance = sigma^2/pop
reg prob workplace smokes [aw=pop]

* Alternatively, we can do WLS by hand
gen w=sqrt(pop)
gen y=prob*w
gen x1=workplace*w
gen x2=smokes*w
reg y x1 x2 w, nocons  /* we need to suppress the constant */

