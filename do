rm sdr*
cd sdr-she*
make clean
dpkg-buildpackage -k5ED67C93 
cd ..
dput debexpo *changes
git commit -a -m "new build"
git push
