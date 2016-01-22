## If the R package TIMP is not installed, please run:
## install.packages("TIMP")

require(TIMP) 

## simulate a 101 x 41 matrix of data

times <- seq(0, 300, by=7.5)
wavenum <- seq(18000, 28000, by=100)
irf = FALSE
irfvec = vector()

location <- c(26000, 23000, 20000) 
delta <- c(2000, 3000, 4000)
amp <- c(1, 2, 3)  
E <- matrix(nrow = length(wavenum), ncol = length(location))

E[, 1] <- amp[1] * exp( - log(2) * (2 * (wavenum - location[1])/delta[1])^2)
E[, 2] <- amp[2] * exp( - log(2) * (2 * (wavenum - location[2])/delta[2])^2)
E[, 3] <- amp[3] * exp( - log(2) * (2 * (wavenum - location[3])/delta[3])^2)

PSI <- matrix(nrow=length(times), ncol = length(wavenum))


for (i in 1:length(wavenum)) {
#     irfvec <- irfparF(irfpar = c(57.47680283, 1.9), lambdac = 1500, 
#     lambda = wavenum[i], i=1, mudisp = TRUE, parmu = c(.001,.001), 
#     dispmufun = "poly", taudisp = FALSE, disptaufun="",partau=vector())

#     cohirf <- irfparF(irfpar = c(57.47680283, 1.9), lambdac = 1200, lambda =
#     wavenum[i], i=1, mudisp = TRUE, parmu = c(.0001,.0001), taudisp = FALSE,
#     dispmufun = "poly")

    C <- compModel (k=c(.01,.05,0.9), x=times, irfpar =irfvec, # cohirf = cohirf, 
    irf = irf, # cohspec = list(type = "freeirfdisp"),coh = vector(), 
    lamb = i, dataset = 1,usekin2=FALSE) 
    
    PSI[,i] <- C %*% as.matrix(E[i,])    
}    

sigma <- .01
PSI  <- PSI + sigma * rnorm(dim(C)[1] * dim(E)[1])

# write.table(rbind(c(c(0),wavenum,c(1234321234)),cbind(times,PSI,rep(1234321234,length(times)))),
# file='3expdata.csv',row.names = FALSE,col.names=FALSE,sep=',')

ser2 <- dat(psi.df = PSI, x = times, nt = length(times), x2 = wavenum, nl =
length(wavenum)) 

model1<- initModel(mod_type = "kin", 
kinpar=c(.01, .05,0.8), # lambdac = 1200, 
# irfpar=c(57.47680283, 1.9), 
irf = FALSE,
#parmu = list(c(.001,.001), c(.0001,.0001)), 
seqmod=FALSE, # cohspec = list(type="freeirfdisp"),
makeps="Sergey data", title="Ser")

## fit the model 

serRes<-fitModel(list(ser2), list(model1), 
opt=kinopt(iter=11, plot = TRUE))
