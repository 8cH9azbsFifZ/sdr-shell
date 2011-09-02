cd sdr-she*
#make clean
rm debian/debhelper.log

#./debian/rules get-orig-source
#mv sdr*gz ..

debuild
debuild -S
#dpkg-buildpackage -k5ED67C93 

cd ..
cd sdr-she*
make clean
rm debian/debhelper.log
cd ..

#dput debexpo *changes
git commit -a -m "new build"
git push


lintian --pedantic --all *dsc
lintian  *deb

