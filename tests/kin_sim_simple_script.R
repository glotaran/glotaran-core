## If the R package TIMP is not installed, please run:
## install.packages("TIMP")

require(TIMP) 

## simulate a 101 x 41 matrix of data
set.seed(123)
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

kinpar <- c(.005,.05,0.09)
startkinpar <- c(.01, .05,0.08)


C <- compModel (k=kinpar, x=times, irfpar =irfvec, # cohirf = cohirf, 
irf = irf, # cohspec = list(type = "freeirfdisp"),coh = vector(), 
lamb = i, dataset = 1,usekin2=FALSE) 

firstC <- compModel (k=startkinpar, x=times, irfpar =irfvec, # cohirf = cohirf, 
irf = irf, # cohspec = list(type = "freeirfdisp"),coh = vector(), 
lamb = i, dataset = 1,usekin2=FALSE) 
       
for (i in 1:length(wavenum)) {
#     irfvec <- irfparF(irfpar = c(57.47680283, 1.9), lambdac = 1500, 
#     lambda = wavenum[i], i=1, mudisp = TRUE, parmu = c(.001,.001), 
#     dispmufun = "poly", taudisp = FALSE, disptaufun="",partau=vector())

#     cohirf <- irfparF(irfpar = c(57.47680283, 1.9), lambdac = 1200, lambda =
#     wavenum[i], i=1, mudisp = TRUE, parmu = c(.0001,.0001), taudisp = FALSE,
#     dispmufun = "poly")

    PSI[,i] <- C %*% as.matrix(E[i,])    
}    

sigma <- .01
PSI  <- PSI + sigma * rnorm(dim(C)[1] * dim(E)[1])

# First use variable projection to calculate the conditional linear 
# parameters (clp) from C and PSI. Here ET stand for estimated E^T.
ET <- matrix(nrow=length(kinpar), ncol = length(wavenum))
    # for each dimension that is not time (in this case just wavelength)
    for (i in 1:dim(PSI)[2]) {
        ET[,i] <- qr.coef(qr(C), PSI[,i])
    }
# 
clp = t(ET)
dev.new()
matplot(clp)
# obviously in R this can be done more efficiently for all wavelengths simultanously,
# but this will only work if all the dimension are the same:
# The spectra
dev.new()
clpplot <- matplot(t(qr.coef(qr(C), PSI)))
# The fitted data (length(times)) number of spectra
dev.new()
matplot(t(qr.fitted(qr(C), PSI)))
# The residuals at each timepoint
dev.new()
matplot(t(qr.resid(qr(C), PSI)))


# This commented dfunction writes out the simulated data, with a bogus number appended to each lin
# so that this can easily be replace by a space in order to translate it into a 1D vector.
# write.table(rbind(c(c(0),wavenum,c(1234321234)),cbind(times,PSI,rep(1234321234,length(times)))),
# file='3expdata.csv',row.names = FALSE,col.names=FALSE,sep=',')
# sed -i 's:1234321234::g' 3expdata.csv

ser2 <- dat(psi.df = PSI, x = times, nt = length(times), x2 = wavenum, nl =
length(wavenum)) 

model1<- initModel(mod_type = "kin", 
kinpar=c(.01, .05,0.08), # lambdac = 1200, 
# irfpar=c(57.47680283, 1.9), 
irf = FALSE,
#parmu = list(c(.001,.001), c(.0001,.0001)), 
seqmod=FALSE, # cohspec = list(type="freeirfdisp"),
makeps="Sergey data", title="Ser")

## fit the model 

serRes<-fitModel(list(ser2), list(model1), 
opt=kinopt(iter=11, plot = TRUE))

# compare the results with the varpro we did earlier
dev.new()
clp2 <- getCLP(serRes)
matplot(cbind(clp,clp2))

