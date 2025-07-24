#include "FileInspector.h"
#include "FileTask.h"

#include <iostream>
#include <utility>
#include <sys/wait.h>
#include <unistd.h>

FileInspector::FileInspector(const std::vector<std::string>& files, std::string  snapshotDir)
    : _filePaths(files), _snapshotDir(std::move(snapshotDir)) {}

void FileInspector::run() {
    std::vector<pid_t> childPIDs;

    for (const std::string& filePath : _filePaths) {
        pid_t pid = fork();

        if (pid < 0) {
            std::cerr << "Fork failed for file " << filePath << '\n';
            continue;
        }

        if (pid == 0) {
            FileTask task(filePath, _snapshotDir);
            task.run();
            _exit(0);
        }

        childPIDs.push_back(pid);
    }

    for (pid_t pid : childPIDs) {
        int status;
        waitpid(pid, &status, 0);
        std::cout << "Child: " << pid << " completed with status: " << status << '\n';
    }
}
