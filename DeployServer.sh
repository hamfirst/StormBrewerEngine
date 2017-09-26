#!/bin/bash
git -C $PROJECT_DIR pull
make -j 4

if [[ $? != 0 ]]; 
  then exit $?; 
fi

killcmd='kill -9 `cat ~/'$PROJECT_NAME'/ServerExe.pid`'
ssh 52.161.102.44 $killcmd
scp ServerExe 52.161.102.44:~/$PROJECT_NAME
rsync -r -a -v -e ssh --delete ~/$PROJECT_NAME/Test/Assets/ 52.161.102.44:~/$PROJECT_NAME/Assets/

runcmd='cd '$PROJECT_NAME' && ./ServerExe -D'
ssh 52.161.102.44 $runcmd


