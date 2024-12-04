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
        // Çocuk süreci
		FILE *file = fopen("dosya.txt", "r"); 
		if (file == NULL) { 
		// Dosya bulunamadı 
		fprintf(stderr, "Dosya açılamadı, abort() çağrılıyor\n"); 
		abort(); 
		} else { 
		// Dosya başarıyla açıldı 
		fclose(file); 
		printf("Dosya başarıyla açıldı\n"); 
		exit(0); 
		}
    } else {
		int durum; 
		wait(&durum); 
		if (WIFEXITED(durum)) { 
		printf("Child process sinyal ile sonlandı, sinyal numarası: %d\n", WTERMSIG(status));
		} else if (WIFEXITED(status)) { 
			printf("Child process düzgün bir şekilde tamamlandı, çıkış durumu: %d\n" WEXITSTATUS(status)); 
		} else { 
			printf("Child process beklenmedik şekilde sonlandı\n"); 
		}
    }
    printf("Program sonlanıyor. Ebeveyn PID: %d\n", getpid());
    return 0;
}