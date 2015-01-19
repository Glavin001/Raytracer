make clean
make
./bin/raytracer.o -input in/scene1_01.txt -size 200 200 -output out/scene1_01.bmp -depth 9 10 f
./bin/raytracer.o -input in/scene1_02.txt -size 200 200 -output out/scene1_02.bmp -depth 8 12 f
./bin/raytracer.o -input in/scene1_03.txt -size 200 200 -output out/scene1_03.bmp -depth 8 12 f
./bin/raytracer.o -input in/scene1_04.txt -size 200 200 -output out/scene1_04.bmp -depth 12 17 f
./bin/raytracer.o -input in/scene1_05.txt -size 200 200 -output out/scene1_05.bmp -depth 14.5 19.5 f
./bin/raytracer.o -input in/scene1_06.txt -size 200 200 -output out/scene1_06.bmp -depth 3 7 f
./bin/raytracer.o -input in/scene1_07.txt -size 200 200 -output out/scene1_07.bmp -depth -2 2 f
