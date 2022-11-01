import qbs

Project {

    QtApplication {
        consoleApplication: true
        install: true
        Depends { name: "qcron-lib" }
        files: [
            "main.cpp",
        ]
    }

    Library {
        id: qCronLib
        property string thirdPartyQCronSrcPath: "3rdparty/qcron/src"
        type: "staticlibrary"
        name: "qcron-lib"
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        files: [
            qCronLib.thirdPartyQCronSrcPath + "/" + "holiday.hpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "qcron.hpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "qcronfield.hpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "qcronnode.hpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "holiday.cpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "qcron.cpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "qcronfield.cpp",
            qCronLib.thirdPartyQCronSrcPath + "/" + "qcronnode.cpp"
        ]
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [ qCronLib.thirdPartyQCronSrcPath ]
       }
    }

}
