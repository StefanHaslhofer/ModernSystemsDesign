int write(int fd, const char *buf, int size);

const char text[] = "Hello World!\n";

int main ( ) {
	write(0, text, sizeof(text));
    return 0;
}
