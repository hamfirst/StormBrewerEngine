#!/bin/bash

export PROJECT_DIR=`pwd`

return_val=""
read_var_with_default() {

    local inp=""
    if [[ "$2" = true ]]; then

        while [[ -z ${inp} ]]; do

            if [[ -z $3 ]]; then
                echo $1" (Required): "
                read inp
            else
                echo $1" [Default is" $3"] (Required): "
                read inp

                if [[ -z  ${inp} ]]; then
                    inp=$3
                fi
            fi
        done
    else
        if [[ -z $3 ]]; then
            echo $1": "
            read inp
        else
            echo $1" [Default is" $3"]: "
            read inp

            if [[ -z  ${inp} ]]; then
                inp=$3
            fi
        fi
    fi

    return_val=${inp}
}

echo "Setting up project environment settings"

if [[ -z ${QT_DIR} && -d ~/Qt/5.11.1/gcc_64 ]]; then
    QT_DIR=~/Qt/5.11.1/gcc_64
fi

if [[ -z ${CLANG_HEADER_PATH} && -d /usr/local/lib/clang/8.0.0/include ]]; then
    CLANG_HEADER_PATH=/usr/local/lib/clang/8.0.0/include
fi

read_var_with_default "Enter QT Directory" true ${QT_DIR}
export QT_DIR=${return_val}

read_var_with_default "Enter Clang Header Directory" true ${CLANG_HEADER_PATH}
export CLANG_HEADER_PATH=${return_val}

read_var_with_default "Enter Emcripten SDK Directory" false ${EM_SDK_PATH}
export EM_SDK_PATH=${return_val}

rm ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
touch ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt

echo "QT_DIR="${QT_DIR} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "CMAKE_DIR=" >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "MINGW_DIR=" >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "CLANG_HEADER_PATH="${CLANG_HEADER_PATH} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "EM_SDK_PATH="${EM_SDK_PATH} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "VC_PATH=" >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt

git update-index --skip-worktree ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
