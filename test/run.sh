
echo "=== Cleaning ==="
make clean

echo "=== Compile Raytracer ==="
make

echo "=== Render all input files ==="
IN_DIR=in/
OUT_DIR=out/
IN_FILES=${IN_DIR}*.txt
for f in $IN_FILES
do
    filename=$(basename ${f})
    echo "===== Processing scene file '$filename'... ====="

    cmd="./bin/raytracer.o -input ${IN_DIR}${filename} -size 200 200 -output ${OUT_DIR}${filename%%.*}.bmp"
    echo ${cmd}

    # Execute command
    ${cmd}

    echo "\n"

done

echo "=== Render input files with depth ==="
./bin/raytracer.o -input in/scene1_01.txt -size 200 200 -output out/scene1_01.bmp -depth 9 10 out/depth1_01.bmp
./bin/raytracer.o -input in/scene1_02.txt -size 200 200 -output out/scene1_02.bmp -depth 8 12 out/depth1_02.bmp
./bin/raytracer.o -input in/scene1_03.txt -size 200 200 -output out/scene1_03.bmp -depth 8 12 out/depth1_03.bmp
./bin/raytracer.o -input in/scene1_04.txt -size 200 200 -output out/scene1_04.bmp -depth 12 17 out/depth1_04.bmp
./bin/raytracer.o -input in/scene1_05.txt -size 200 200 -output out/scene1_05.bmp -depth 14.5 19.5 out/depth1_05.bmp
./bin/raytracer.o -input in/scene1_06.txt -size 200 200 -output out/scene1_06.bmp -depth 3 7 out/depth1_06.bmp
./bin/raytracer.o -input in/scene1_07.txt -size 200 200 -output out/scene1_07.bmp -depth -2 2 out/depth1_07.bmp
./bin/raytracer.o -input in/scene1_08.txt -size 200 200 -output out/scene1_08.bmp -depth 0 10 out/depth1_08.bmp

./bin/raytracer.o -input in/scene2_04_perspective.txt -size 200 200 -output out/scene2_04_perspective.bmp -depth 8 12 out/depth2_04_perspective.bmp
