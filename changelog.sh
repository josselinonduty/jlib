#!/bin/bash

RELEASE_TAG=$(git describe --tags --abbrev=0 HEAD)
PREVIOUS_TAG=$(git describe --tags --abbrev=0 HEAD^)

IS_WIP=$([ "${PREVIOUS_TAG}" == "${RELEASE_TAG}" ] && echo "true" || echo "false")
if [ "${IS_WIP}" == "true" ]; then
    RELEASE_TAG=$(git describe --tags HEAD)
    echo "# CHANGELOG - (WIP) ${RELEASE_TAG}"
else
    echo "# CHANGELOG - ${RELEASE_TAG}"
fi

echo ""
echo "<sub>Last modification: $(git log -1 --pretty='format:%cd' --date=format:'%Y-%m-%d %H:%M' ${RELEASE_TAG})</sub>"

echo ""
echo "## Commits"
echo ""

git log ${PREVIOUS_TAG}..${RELEASE_TAG} --no-merges --first-parent --pretty=format:"- %s (%an <%ae>)"

echo ""
echo ""
echo "## Contributors"
echo ""
git shortlog -esn --no-merges ${PREVIOUS_TAG}..${RELEASE_TAG}