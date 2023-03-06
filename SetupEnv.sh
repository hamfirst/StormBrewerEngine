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

if [[ -z ${QT_DIR} && -d ~/Qt/5.15.2 ]]; then
    QT_DIR=~/Qt/5.15.2/
fi

if [[ -z ${LLVM_ROOT_PATH} && -d ~/llvm-project ]]; then
    LLVM_ROOT_PATH=~/llvm-project
fi

if [[ -z ${LLVM_BUILD_PATH} && -d ~/llvm-project/build ]]; then
    LLVM_BUILD_PATH=~/llvm-project/build
fi

read_var_with_default "Enter QT Directory" true ${QT_DIR}
export QT_DIR=${return_val}

read_var_with_default "Enter LLVM Root Directory" true ${LLVM_ROOT_PATH}
export LLVM_ROOT_PATH=${return_val}

read_var_with_default "Enter LLVM Build Directory" true ${LLVM_BUILD_PATH}
export LLVM_BUILD_PATH=${return_val}

read_var_with_default "Enter Emcripten SDK Directory" false ${EM_SDK_PATH}
export EM_SDK_PATH=${return_val}

rm ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
touch ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt

echo "QT_DIR="${QT_DIR} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "CMAKE_DIR=" >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "MINGW_DIR=" >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "LLVM_ROOT_PATH="${LLVM_ROOT_PATH} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "LLVM_BUILD_PATH="${LLVM_BUILD_PATH} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "EM_SDK_PATH="${EM_SDK_PATH} >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
echo "VC_PATH=" >> ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt

git update-index --skip-worktree ${PROJECT_DIR}/ProjectSettings/ProjectEnv.txt
