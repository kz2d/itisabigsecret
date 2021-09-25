#include <stdio.h>
#include <stdlib.h>
#include "archive.h"
#include "unarchive.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    SETTINGS *settings = createSettings(argc, argv);
    printSettings(settings);

    if (settings->LIST)
    {
        list(createUnarchive(settings->inputFile));
    }
    else if (settings->EXTRACT)
    {
        unmakeArchive(createUnarchive(settings->inputFile));
    }
    else if (settings->CREATE)
    {
        makeArchive(createArchive(settings->fileCount, settings->fileNames, settings->inputFile));
    }
    // ARCHIVE *arc = createArchive(2, a, "kek");
    // printArchive(arc);
    // makeArchive(arc);
    // UNARCHIVE *unarc = createUnarchive("kek");
    // unmakeArchive(unarc);
    return 0;
}