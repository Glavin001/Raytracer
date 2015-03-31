#!/bin/bash
shopt -s extglob

IN_DIR=in/
OUT_DIR=../out/ # Relative from within $IN_DIR
EXT="bmp" # or "tga"
BIN=../bin/raytracer.o # Relative from within $IN_DIR

startDate=$(date +"%s")

# echo "=== Cleaning ==="
# make clean

# echo "=== Compile Raytracer ==="
# make

echo "=== Move into '${IN_DIR}' ==="
cd ${IN_DIR}

echo
echo "=== Render all input files ==="
OMP_NUM_THREADS=8

# Default to all input files
IN_FILES=*.txt

# Check 1 argument is given #
if [ $# -eq 1 ]
then
        echo "Render input files with pattern: $1"
        IN_FILES=@($1)
fi

echo
echo "=== Render input files ==="
for f in $IN_FILES
do
    filename=$(basename ${f})
    echo
    echo "===== Processing scene file '$filename' ====="
    filenameNoExt=${filename%%.*}
    echo

    echo "--> $filename - Output & Normals"
    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}-no_back.${EXT} -normals ${OUT_DIR}${filenameNoExt}_normals.${EXT}"
    echo "  cd ${IN_DIR} ; ${cmd} ; cd ../"
    # Execute command
    ${cmd}
    echo

    echo "--> $filename - Shadows"
    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}-shadows.${EXT} -shadows"
    echo "  cd ${IN_DIR} ; ${cmd} ; cd ../"
    # Execute command
    ${cmd}
    echo

    echo "--> $filename - Shade Back"
    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}-shade_back.${EXT} -shade_back"
    echo "  cd ${IN_DIR} ; ${cmd} ; cd ../"
    # Execute command
    ${cmd}
    echo

    echo "--> $filename - Shade Back & Shadows & 5 Bounces"
    cmd="${BIN} -input ${filename} -size 200 200 -output ${OUT_DIR}${filenameNoExt}-shadows_shade_back.${EXT} -shade_back -shadows -bounces 5"
    echo "  cd ${IN_DIR} ; ${cmd} ; cd ../"
    # Execute command
    ${cmd}

    echo

done

# Check 1 argument is given #
if [ $# -eq 1 ]
then

    echo
    echo "=== Note ==="
    echo "This is *not* rendering special test input files."
    echo "Please use 'make render' and *not* 'make render-file' to render *all* input files"
    echo

else

    echo
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

    echo
    echo "=== Render input files with reflection bounces ==="
    ${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_0.${EXT} -bounces 0
    ${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_1.${EXT} -bounces 1
    ${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_2.${EXT} -bounces 2
    ${BIN} -input scene_reflective_sphere.txt -size 200 200 -output ${OUT_DIR}scene_reflective_sphere_bounces_3.${EXT} -bounces 3

    ${BIN} -input scene4_06_transparent_bars.txt -size 200 200 -output ${OUT_DIR}scene4_06_transparent_bars-bounces_0.${EXT} -bounces 0 -shade_back -shadows
    ${BIN} -input scene4_06_transparent_bars.txt -size 200 200 -output ${OUT_DIR}scene4_06_transparent_bars-bounces_1.${EXT} -bounces 1 -shade_back -shadows
    ${BIN} -input scene4_06_transparent_bars.txt -size 200 200 -output ${OUT_DIR}scene4_06_transparent_bars-bounces_2.${EXT} -bounces 2 -shade_back -shadows
    ${BIN} -input scene4_06_transparent_bars.txt -size 200 200 -output ${OUT_DIR}scene4_06_transparent_bars-bounces_3.${EXT} -bounces 3 -shade_back -shadows
    ${BIN} -input scene4_06_transparent_bars.txt -size 200 200 -output ${OUT_DIR}scene4_06_transparent_bars-bounces_4.${EXT} -bounces 4 -shade_back -shadows
    ${BIN} -input scene4_06_transparent_bars.txt -size 200 200 -output ${OUT_DIR}scene4_06_transparent_bars-bounces_5.${EXT} -bounces 5 -shade_back -shadows

    # High Res Examples
    # ${BIN} -input scene_reflective_sphere.txt -size 1000 1000 -output ${OUT_DIR}scene_reflective_sphere.${EXT}
    # ${BIN} -input scene_reflective_shininess_variations.txt -size 1000 1000 -output ${OUT_DIR}scene_reflective_shininess_variations.${EXT}

fi

echo "=== Move back out of '${IN_DIR}' ==="
cd ..

echo
echo "=== Time Elapse ==="
endDate=$(date +"%s")
diff=$(($endDate-$startDate))
echo "$(($diff / 60)) minutes and $(($diff % 60)) seconds elapsed."
