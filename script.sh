#!/bin/bash
export "GIT_AUTHOR_DATE=$1 +0000"
export "GIT_COMMITTER_DATE=$1 +0000"
git add .
git commit -m "$2"
