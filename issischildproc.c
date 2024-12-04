#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    // Çocuk süreci oluştur
    pid = fork();
	
    printf("Program başladı. Ebeveyn PID: %d\n", getpid());

    if (pid < 0) {
        // Hata durumu
        perror("Fork başarısız!");
        return 1;
    } else if (pid == 0) {
        // Çocuk süreci, dosyayı oku
		execlp("/bin/cat", "cat", "dosya.txt", NULL);
        // Eğer execlp başarısız olursa
        perror("execlp başarısız!");
        return 1;
    } else {
		int durum; 
		wait(&durum); 
		if (WIFEXITED(durum)) { 
		printf("Child process tamamlandı, çıkış durumu: %d\n", WEXITSTATUS(durum)); 
		} else { 
		printf("Child process beklenmedik bir şekilde sonlandı\n"); 
		}
    }
    printf("Program sonlanıyor. Ebeveyn PID: %d\n", getpid());
    return 0;
}