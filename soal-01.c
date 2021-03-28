/* EL2208 Praktikum Pemecahan Masalah dengan C
*Modul       : 6
*Percobaan   : 
*Hari/Tanggal: 
*Nama/NIM    : Oktavianus Irvan Sitanggang/13218071
*Asisten/NIM : 
*Nama File   : 
*Deskripsi   : Isi Deskripsi
*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int load;
    struct node* next;
};

void push(struct node** head, int newLoad){
    // Push new Load to head
    // Dilakukan dengan mengelompokkan yang sama sehingga yang sama bersebelahan
    if (*head == NULL){    // jika sudah kosong, mkaa diletakkan di paling akhir
        struct node *temp;
        temp = (struct node *)malloc(sizeof(struct node));
        temp->load = newLoad;
        temp->next = (*head);
        (*head) = temp;
    }
    else if ((*head)->load == newLoad){ // jika sama, maka load baru tiletakkan di depan head ini
        struct node *temp;
        temp = (struct node *)malloc(sizeof(struct node));
        temp->load = newLoad;
        temp->next = (*head);
        (*head) = temp;
    }
    else { // check next 
        push(&((*head) -> next), newLoad);
    }    
}

int pop (struct node **head){
    int ans = (*head)->load;
    (*head) = (*head)->next;
    return ans;
}

void printNode(struct node* head){
    struct node* current = head;
    current = (struct node*)malloc(sizeof(struct node));
    current = head;
    printf("|Kepala|");
    while(current->next != NULL){
        printf("-.-|%d|", current->load);
        current = current->next;
    }
    printf("-.-|%d|\n", current->load);
}

struct node* deleteDuplicate(struct node** head, struct node **tempHead){
    if ((*head)->next == NULL) { // jika next sudah nol, maka tidak ada duplikasi lagi
        return (*head);
    }
    else if ((*head)->load == ((*head)->next)->load){ // rekursi untuk selanjutnya
        int ans = pop(head); // mengeluarkan paling atas dari load, kemudian di push ke temphead
        push (tempHead, ans); 

        struct node *temp;
        temp = (struct node *)malloc(sizeof(struct node));

        temp = deleteDuplicate(&((*head)), tempHead); // rekrusi karena elemen sebelumnya sudah dihapus

        return (*head);
    }
    else{
        struct node *temp;
        temp = (struct node *)malloc(sizeof(struct node));

        temp = deleteDuplicate(&((*head)->next), tempHead); // rekursi, cek setelahnya karena tidak ada duplikasi

        (*head)->next = temp;
        return (*head);
    }
}

int main(){
    int n;
    int i,j,k;
    scanf("%d",&n);

    // no load in train
    if (n <= 0){
        printf("Muatan kosong\n");
        return 1;
    }

    struct node *head;
    head = (struct node*)malloc(sizeof(struct node));

    int temp;
    scanf("%d",&temp);
    head->load = temp;
    head->next = NULL;
    for (i=1 ; i < n; i++){
        scanf("%d",&temp);
        push(&head,temp);
    }
    
    struct node *tempHead = NULL;
    printf("In :\n");
    printNode(head);
    deleteDuplicate(&head, &tempHead);
    printf("Out:\n");
    printNode(head);

    while (tempHead != NULL){ // jika masih ada temphead, maka masih ada muatan yang ditempatkan ke kereta
        head = tempHead;
        tempHead = NULL;
        deleteDuplicate(&head, &tempHead);
        printNode(head);
    }
    
    return 0;
}
