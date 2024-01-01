#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TODO 100
#define MAX_LIST 100
#define FILE_NAME "todo_db.txt"

struct Todo
{
	int id;
	char todoList[MAX_LIST];
	char date[MAX_LIST];
	char desc[MAX_LIST];
	char status[10];
};

// Membuat Daftar To do List
void createTodo(struct Todo todo[], int *count)
{
	struct Todo newTodo;
	printf("\nMasukkan ID Todo: ");
	scanf("%d", &newTodo.id);

	// Cek apakah ID sudah terdaftar
	for (int i = 0; i < *count; i++)
	{
		if (todo[i].id == newTodo.id)
		{
			printf("ID SUDAH TERDAFTAR\n");
			return;
		}
	}

	printf("Masukkan Tugas Baru: ");
	scanf(" %[^\n]s", newTodo.todoList);
	printf("Masukkan tanggal Deadline: ");
	scanf(" %[^\n]s", newTodo.date);
	printf("Masukkan Deskripsi Tugas: ");
	scanf(" %[^\n]s", newTodo.desc);
	strcpy(newTodo.status, "Belum Selesai");

	todo[*count] = newTodo;
	(*count)++;

	FILE *file = fopen(FILE_NAME, "a");
	if (file == NULL)
	{
		printf("Gagal membuka file\n");
		return;
	}

	fprintf(file, "\nID : %d", newTodo.id);
	fprintf(file, "\nTodo : %s", newTodo.todoList);
	fprintf(file, "\nTanggal Deadline : %s", newTodo.date);
	fprintf(file, "\nDeskripsi Todo : %s", newTodo.desc);
	fprintf(file, "\nStatus : %s", newTodo.status);
	fclose(file);

	printf("Tugas berhasil ditambahkan\n");
}

// Menampilkan Daftar To do list
void displayTodo(struct Todo todo[], int count)
{
	if (count == 0)
	{
		printf("\nBelum ada tugas yang terdaftar\n");
		return;
	}
	printf("\n----------------------------\n");
	printf("Daftar Todo List:\n");
	for (int i = 0; i < count; i++)
	{
		printf("ID: %d\n", todo[i].id);
		printf("Todo: %s\n", todo[i].todoList);
		printf("Tanggal Selesai: %s\n", todo[i].date);
		printf("Status: %s\n", todo[i].status);
		printf("Deskripsi: %s\n", todo[i].desc);
		printf("----------------------------\n");
	}
}

// Memperbarui atau update To do list
void updateTodo(struct Todo todo[], int count)
{
	int id;
	printf("Masukkan ID tugas yang ingin diupdate: ");
	scanf("%d", &id);

	int found = 0;
	for (int i = 0; i < count; i++)
	{
		if (todo[i].id == id)
		{
			printf("\nMasukkan kegiatan tugas baru: ");
			scanf(" %[^\n]s", todo[i].todoList);
			printf("Masukkan tanggal Deadline baru: ");
			scanf(" %[^\n]s", todo[i].date);
			printf("Masukkan deskripsi tugas baru: ");
			scanf(" %[^\n]s", todo[i].desc);

			found = 1;
			break;
		}
	}

	if (!found)
	{
		printf("Tugas dengan ID tersebut tidak ditemukan\n");
	}
	else
	{
		FILE *file = fopen(FILE_NAME, "w");
		if (file == NULL)
		{
			printf("Gagal membuka file\n");
			return;
		}

		for (int i = 0; i < count; i++)
		{
			fprintf(file, "\nID : %d", todo[i].id);
			fprintf(file, "\ntodoList : %s", todo[i].todoList);
			fprintf(file, "\nTanggal Deadline : %s", todo[i].date);
			fprintf(file, "\nDeskripsi : %s", todo[i].desc);
			fprintf(file, "\nStatus : %s", todo[i].status);
		}

		fclose(file);
		printf("Tugas berhasil diupdate\n");
	}
}

// Menghapus Daftar To do list
void deleteTodo(struct Todo todo[], int *count)
{
	int id;
	printf("Masukkan ID tugas yang ingin dihapus: ");
	scanf("%d", &id);

	int found = 0;
	for (int i = 0; i < *count; i++)
	{
		if (todo[i].id == id)
		{
			found = 1;
			for (int j = i; j < *count - 1; j++)
			{
				todo[j] = todo[j + 1];
			}
			(*count)--;
			break;
		}
	}

	if (!found)
	{
		printf("Tugas dengan ID tersebut tidak ditemukan\n");
	}
	else
	{
		FILE *file = fopen(FILE_NAME, "w");
		if (file == NULL)
		{
			printf("Gagal membuka file\n");
			return;
		}

		for (int i = 0; i < *count; i++)
		{
			fprintf(file, "%d,%s,%s,%s\n", todo[i].id, todo[i].todoList, todo[i].date, todo[i].desc);
		}

		fclose(file);
		printf("Tugas berhasil dihapus\n");
	}
}

// menandai tugas kalau sudah selesai atau belum
void markTodoComplete(struct Todo todo[], int count)
{
	int id;
	printf("Masukkan ID tugas yang ingin ditandai selesai: ");
	scanf("%d", &id);

	int found = 0;
	for (int i = 0; i < count; i++)
	{
		if (todo[i].id == id)
		{
			strcpy(todo[i].status, "Selesai");
			found = 1;
			break;
		}
	}

}

int main()
{
	struct Todo todo[MAX_TODO];
	int count = 0;

	FILE *file = fopen(FILE_NAME, "r");
	if (file != NULL)
	{
		char line[256];
		while (fgets(line, sizeof(line), file))
		{
			sscanf(line, "ID : %d", &todo[count].id);
			fgets(line, sizeof(line), file);
			sscanf(line, "todoList : %[^\n]", todo[count].todoList);
			fgets(line, sizeof(line), file);
			sscanf(line, "date : %[^\n]", todo[count].date);
			fgets(line, sizeof(line), file);
			sscanf(line, "desc : %[^\n]", todo[count].desc);

			count++;
		}
		fclose(file);
	}

	printf("Selamat datang di Program Todo List\n");
	printf("Program ini digunakan untuk menambah, menampilkan, mengupdate, dan menghapus Todo List\n");

	char choice;
	do
	{
		printf("\nMenu:\n");
		printf("a. Tambah Tugas Baru\n");
		printf("b. Tampilkan Daftar Tugas\n");
		printf("c. Update Informasi Tugas\n");
		printf("d. Tandai Tugas Selesai\n");
		printf("e. Hapus Tugas\n");
		printf("f. Keluar\n");
		printf("Pilihan Anda: ");
		scanf(" %c", &choice);

		switch (choice)
		{
		case 'a':
			createTodo(todo, &count);
			break;
		case 'b':
			displayTodo(todo, count);
			break;
		case 'c':
			updateTodo(todo, count);
			break;
		case 'd':
			markTodoComplete(todo, count);
			break;
		case 'e':
			deleteTodo(todo, &count);
			break;
		case 'f':
			exit (0);
			break;
		default:
			printf("Pilihan tidak valid\n");
		}
	}
	while (choice != 'f');

	return 0;
}

