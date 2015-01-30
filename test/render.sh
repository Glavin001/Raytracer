IN_DIR=in/
OUT_DIR=../out/ # Relative from within $IN_DIR
BIN=../bin/raytracer.o # Relative from within $IN_DIR

echo "=== Cleaning ==="
make clean

echo "=== Compile Raytracer ==="
make

echo "=== Move into '${IN_DIR}' ==="
cd ${IN_DIR}

echo "=== Render all input files ==="
IN_FILES=*.txt
for f in $IN_FILES
do
    filename=$(basename ${f})
    echo "===== Processing scene file '$filename'... ====="
    filenameNoExt=${filename%%.*}

    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}.bmp -normals ${OUT_DIR}normal_${filenameNoExt}.bmp"
    echo ${cmd}

    # Execute command
    ${cmd}

    echo "\n"

done

echo "=== Render input files with depth ==="
${BIN} -input scene1_01.txt -size 200 200 -output ${OUT_DIR}scene1_01.bmp -depth 9 10 ${OUT_DIR}depth1_01.bmp
${BIN} -input scene1_02.txt -size 200 200 -output ${OUT_DIR}scene1_02.bmp -depth 8 12 ${OUT_DIR}depth1_02.bmp
${BIN} -input scene1_03.txt -size 200 200 -output ${OUT_DIR}scene1_03.bmp -depth 8 12 ${OUT_DIR}depth1_03.bmp
${BIN} -input scene1_04.txt -size 200 200 -output ${OUT_DIR}scene1_04.bmp -depth 12 17 ${OUT_DIR}depth1_04.bmp
${BIN} -input scene1_05.txt -size 200 200 -output ${OUT_DIR}scene1_05.bmp -depth 14.5 19.5 ${OUT_DIR}depth1_05.bmp
${BIN} -input scene1_06.txt -size 200 200 -output ${OUT_DIR}scene1_06.bmp -depth 3 7 ${OUT_DIR}depth1_06.bmp
${BIN} -input scene1_07.txt -size 200 200 -output ${OUT_DIR}scene1_07.bmp -depth -2 2 ${OUT_DIR}depth1_07.bmp
${BIN} -input scene1_08.txt -size 200 200 -output ${OUT_DIR}scene1_08.bmp -depth 0 10 ${OUT_DIR}depth1_08.bmp

${BIN} -input scene2_04_perspective.txt -size 200 200 -output ${OUT_DIR}scene2_04_perspective.bmp -depth 8 12 ${OUT_DIR}depth2_04_perspective.bmp

${BIN} -input test_plane_1.txt -size 200 200 -output ${OUT_DIR}test_plane_1.bmp -depth 0 10 ${OUT_DIR}depth_plane_1.bmp

echo "=== Renderinput files with reflection bounces ==="
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_0.bmp -bounces 0
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_1.bmp -bounces 1
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_2.bmp -bounces 2
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_3.bmp -bounces 3

# High Res Examples
# ${BIN} -input scene_reflective_sphere.txt -size 1000 1000 -output ${OUT_DIR}scene_reflective_sphere.bmp
# ${BIN} -input scene_reflective_shininess_variations.txt -size 1000 1000 -output ${OUT_DIR}scene_reflective_shininess_variations.bmp

echo "=== Move back out of '${IN_DIR}' ==="
cd ..
