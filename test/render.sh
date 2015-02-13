IN_DIR=in/
OUT_DIR=../out/ # Relative from within $IN_DIR
EXT="bmp" # or "tga"
BIN=../bin/raytracer.o # Relative from within $IN_DIR

startDate=$(date +"%s")

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

    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}_no_back.${EXT} -normals ${OUT_DIR}${filenameNoExt}_normals.${EXT}"
    echo ${cmd}
    # Execute command
    ${cmd}

    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}_shadows.${EXT} -shadows"
    echo ${cmd}
    # Execute command
    ${cmd}

    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}_shade_back.${EXT} -shade_back"
    echo ${cmd}
    # Execute command
    ${cmd}

    echo "\n"

done

echo "=== Render input files with depth ==="
${BIN} -input scene1_01.txt -size 200 200 -depth 9 10 ${OUT_DIR}scene1_01_depth.${EXT}
${BIN} -input scene1_02.txt -size 200 200 -depth 8 12 ${OUT_DIR}scene1_02_depth.${EXT}
${BIN} -input scene1_03.txt -size 200 200 -depth 8 12 ${OUT_DIR}scene1_03_depth.${EXT}
${BIN} -input scene1_04.txt -size 200 200 -depth 12 17 ${OUT_DIR}scene1_04_depth.${EXT}
${BIN} -input scene1_05.txt -size 200 200 -depth 14.5 19.5 ${OUT_DIR}scene1_05_depth.${EXT}
${BIN} -input scene1_06.txt -size 200 200 -depth 3 7 ${OUT_DIR}scene1_06_depth.${EXT}
${BIN} -input scene1_07.txt -size 200 200 -depth -2 2 ${OUT_DIR}scene1_07_depth.${EXT}
${BIN} -input scene1_08.txt -size 200 200 -depth 0 10 ${OUT_DIR}scene1_08_depth.${EXT}
${BIN} -input scene2_04_perspective.txt -size 200 200 -depth 8 12 ${OUT_DIR}scene2_04_perspective_depth.${EXT}
${BIN} -input test_plane_1.txt -size 200 200 -depth 0 10 ${OUT_DIR}test_plane_1_depth.${EXT}
${BIN} -input scene2_05_inside_sphere.txt -size 200 200 -depth 9 11 ${OUT_DIR}scene2_05_depth.${EXT} -shade_back
${BIN} -input scene2_06_plane.txt -size 200 200 -depth 8 20 ${OUT_DIR}scene2_06_depth.${EXT}
${BIN} -input scene2_07_sphere_triangles.txt -size 200 200 -depth 9 11 ${OUT_DIR}scene2_07_depth.${EXT} -shade_back

echo "=== Render input files with reflection bounces ==="
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_0.${EXT} -bounces 0
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_1.${EXT} -bounces 1
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_2.${EXT} -bounces 2
${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_3.${EXT} -bounces 3

# High Res Examples
# ${BIN} -input scene_reflective_sphere.txt -size 1000 1000 -output ${OUT_DIR}scene_reflective_sphere.${EXT}
# ${BIN} -input scene_reflective_shininess_variations.txt -size 1000 1000 -output ${OUT_DIR}scene_reflective_shininess_variations.${EXT}

echo "=== Move back out of '${IN_DIR}' ==="
cd ..

endDate=$(date +"%s")
diff=$(($endDate-$startDate))
echo "$(($diff / 60)) minutes and $(($diff % 60)) seconds elapsed."
