#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void create_file() {
    int fd = open("dosya.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Dosya oluşturulamadı");
        exit(1);
    }
    close(fd);
}
void write_file() {
    int fd = open("dosya.txt", O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("Dosya açılamadı");
        exit(1);
    }
    char *data = "Bu, dosyaya yazılan bir örnek veridir.\n";
    write(fd, data, strlen(data));
    close(fd);
}
void read_file() {
    int fd = open("dosya.txt", O_RDONLY);
    if (fd < 0) {
        perror("Dosya açılamadı");
        exit(1);
    }
    char buffer[256];
    int bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer)-1)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }
    close(fd);
}

int main() {
    pid_t pid1, pid2, pid3;

    if ((pid1 = fork()) == 0) {
        // İlk child process: Dosya oluşturma
        create_file();
        exit(0);
    }
    if ((pid2 = fork()) == 0) {
        // İkinci child process: Dosyaya veri yazma
        write_file();
        exit(0);
    }
    if ((pid3 = fork()) == 0) {
        // Üçüncü child process: Dosya içeriğini okuma
        read_file();
        exit(0);
    }
    // Parent process: Tüm child process'lerin tamamlanmasını bekler
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    printf("Tüm child processler tamamlandı.\n");
    return 0;
}
