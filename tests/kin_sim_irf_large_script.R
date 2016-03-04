## If the R package TIMP is not installed, please run:
## install.packages("TIMP")

require(TIMP) 

## simulate a 1022 x 501 matrix of data
set.seed(123)
times1 <- seq(-0.5, 9.98, by=0.02)
times2 <- seq(10, 1500, by=3.0)
times <- c(times1,times2)
wavenum <- seq(12820, 15120, by=4.6)
irf = TRUE
irfvec = c(-0.02,0.05) #location width
# irffun = "gaus" #default is gaus
#             680nm  740nm  690nm  695nm  705 715 730
location <- c(14705, 13513, 14492, 14388, 14184, 13986) 
delta <- c(400, 1000, 300, 200, 350, 330, 310)
amp <- c(1, 0.2, 1, 1, 1, 1, 1)
E <- matrix(nrow = length(wavenum), ncol = length(location))

for (i in 1:length(location)) {
E[, i] <- amp[i] * exp( - log(2) * (2 * (wavenum - location[i])/delta[i])^2)
}

psisim <- matrix(nrow=length(times), ncol = length(wavenum))

kinpar <- c(.006667,.006667, 0.00333, 0.00035, 0.0303, 0.000909)

startkinpar <- c(.005, 0.003, 0.00022, 0.0300, 0.000888)


C <- compModel (k=kinpar, x=times, irfpar =irfvec, # cohirf = cohirf, 
irf = irf, # cohspec = list(type = "freeirfdisp"),coh = vector(), 
lamb = i, dataset = 1,usekin2=FALSE) 

firstC <- compModel (k=startkinpar, x=times, irfpar =irfvec, # cohirf = cohirf, 
irf = irf, # cohspec = list(type = "freeirfdisp"),coh = vector(), 
lamb = i, dataset = 1,usekin2=FALSE) 
       
for (i in 1:length(wavenum)) {
## This is code for generating dispersion (per wavelength dependent irf location)
#     irfvec <- irfparF(irfpar = c(57.47680283, 1.9), lambdac = 1500, 
#     lambda = wavenum[i], i=1, mudisp = TRUE, parmu = c(.001,.001), 
#     dispmufun = "poly", taudisp = FALSE, disptaufun="",partau=vector())

#     cohirf <- irfparF(irfpar = c(57.47680283, 1.9), lambdac = 1200, lambda =
#     wavenum[i], i=1, mudisp = TRUE, parmu = c(.0001,.0001), taudisp = FALSE,
#     dispmufun = "poly")

    psisim[,i] <- C %*% as.matrix(E[i,])    
}    

sigma <- .005
sigma <- .000
psisim  <- psisim + sigma * rnorm(dim(C)[1] * dim(E)[1])

# First use variable projection to calculate the conditional linear 
# parameters (clp) from C and psisim. Here ET stand for estimated E^T.
ET <- matrix(nrow=length(kinpar), ncol = length(wavenum))
    # for each dimension that is not time (in this case just wavelength)
    for (i in 1:dim(psisim)[2]) {
        ET[,i] <- qr.coef(qr(C), psisim[,i])
    }
# 
clp = t(ET)
dev.new()
matplot(clp)
dev.new()
matplot(t(qr.fitted(qr(C), psisim)))


# This commented dfunction writes out the simulated data, with a bogus number appended to each lin
# so that this can easily be replace by a space in order to translate it into a 1D vector.
# write.table(rbind(c(c(0),wavenum,c(1234321234)),cbind(times,psisim,rep(1234321234,length(times)))),
# file='3expdata.csv',row.names = FALSE,col.names=FALSE,sep=',')
# sed -i 's:1234321234::g' 3expdata.csv

ser2 <- dat(psi.df = psisim, x = times, nt = length(times), x2 = wavenum, nl =
length(wavenum)) 

model1<- initModel(mod_type = "kin", 
kinpar=startkinpar, # lambdac = 1200, 
irfpar=c(0.0, 0.1), 
irf = FALSE,
#parmu = list(c(.001,.001), c(.0001,.0001)), 
seqmod=FALSE, # cohspec = list(type="freeirfdisp"),
makeps="Simulate data", title="sim-large")

## fit the model 
ptm <- proc.time()
serRes<-fitModel(list(ser2), list(model1), 
opt=kinopt(iter=11, xlab = "time (ps)", 
ylab = "wavelength", selectedtraces = seq(1,256,by=20), plot = TRUE))
#your function here
print(sprintf("Time taken: %f", (proc.time() - ptm)[3]))


# compare the results with the varpro we did earlier
dev.new()
clp2 <- getCLP(serRes)
matplot(cbind(clp,clp2))

