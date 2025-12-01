cd lib/$1
git pull origin main
cd ..
git commit $1 -m "Updated $1"
git push origin main
