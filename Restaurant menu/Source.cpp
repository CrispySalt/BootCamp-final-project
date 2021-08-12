#include <stdio.h>
#include <stdlib.h>

void asciiART();
void mainMenu(); //ini untuk main menu kaya see menu,list,exit.
void mainMenuChoice();//dipisah dari mainmenu agar gampang, ini buat pilih menu,list,exit.
void delay();//kasih delay.
void longDelay();
void orderList();//untuk output menu,kemudian order menu.
void seeOrder();//lihat orderan sebagai output.
void order();//untuk order makanan.
void payment();
int foodOrder[11];//also edit here to change how much foodMenu there is.

char food[8][30] = {//edit here to change foodMenu.
						 "Red velvet cake (40k)",
						 "Tiramisu (38k)",
						 "Cheese cake (35k)",
						 "Macaroon (25k)",
						 "Cappuccino (30k)",
						 "Espresso (25k)",
						 "Vanilla bean latte (35k)",
						 "Matcha latte (35k)",
};
int foodPrice[8] = { 40,38,35,25,30,25,35,35 };
int foodQuantity[11];
int counter1 = 0;

int main() {
	asciiART();
	printf("Welcome to Tea Corner\n");
	delay();
	mainMenu();
}

void delay() {
	for (int i = 0; i < 1e8; i++) {
		;
	}
}
void longDelay() {
	for (int i = 0; i < 1e9; i++) {
		;
	}
}

void mainMenu() {
	puts("What would you like to do?");
	puts("1. Order");
	puts("2. See your order");
	puts("3. Exit");
	mainMenuChoice();
}

void mainMenuChoice() {
	int i;
	printf("Insert a number:");
	scanf("%d", &i);
	if (i < 1 || i>3) {
		puts("This is an invalid number.");
		mainMenuChoice();
	}
	else if (i == 3) {
		exit(0);
	}
	else if (i == 1) {
		orderList();
	}
	else if (i == 2) {
		seeOrder();
	}
}

void orderList() {
	system("CLS");
	FILE* oc = fopen("order.txt", "r");
	char orderCheck = 'y';
	int size=0;
	if (NULL != oc) {
		fseek(oc, 0, SEEK_END);
		size = ftell(oc);
		fclose(oc);
	}

		if (size > 0) {
			printf("There is already an active order. are you sure(y/n)?\n");
			scanf("%s", &orderCheck);
			getchar();
			system("CLS");
			if (orderCheck == 'n') {
				system("CLS");
				main();
			}
		}
	printf("Menu list:\n");
	for (int s = 0; s < 8; s++) {//Also edit here for foodMenu
		if (s == 0) {
			printf("Dessert\n");
		}
		if (s == 4) {
			printf("\nCoffee & Latte\n");
		}
		printf("%d.%s\n",s+1, food[s]);
	}
	printf("\n");
	int a = 0;
	char orderAgain = 'n';
	while (orderAgain == 'n') {
		for (int a = 0; a < 11; a++) {
			counter1++;
			printf("Your order (food number & quantity):");
			scanf("%d %d", &foodOrder[a],&foodQuantity[a]);
			if (foodOrder[a] >= 9) {
				printf("This number is invalid!\n");
				printf("Defaulting to Matcha latte\n");
				foodOrder[a] = 8;
			}
			printf("Is that all?(y/n)\n");
			scanf("%s", &orderAgain);
			if (orderAgain == 'y') {
				system("CLS");
				payment();
				exit(0);
			}
			if (a == 10) {
				printf("Maximum order reached!\n");
			}
		}
	}

}

void seeOrder() {
	system("CLS");
	FILE* so = fopen("order.txt", "r");//so is SeeOrder.
	char removeOrder = 'no';
	int size = 0;
	if (NULL != so) {
		fseek(so, 0, SEEK_END);
		size = ftell(so);

		if (0 == size) {
			printf("There is no active order.\n");
			printf("Reverting back to main menu.\n");
			longDelay();
			fclose(so);
			system("CLS");
			main();
		}
		else {
			fclose(so);
			FILE* soNew = fopen("order.txt", "r");
			char strings[100][255];
			int counter = 0;
			while (fscanf(soNew, "%[^\n]\n", strings[counter]) != EOF) {
				counter++;
			}
			for (int i = 0; i < counter; i++) {
				printf("%s\n", strings[i]);
			}
			fclose(soNew);
			printf("Would you like to remove order?(yes/no)\n");
			scanf("%s", &removeOrder);
			if (removeOrder == 'y') {
				printf("Order has been removed!\n");
				delay();
				delay();
				delay();
				FILE* co = fopen("order.txt", "w");
				fprintf(co,"");
				fclose(co);//co is Close Order.
			}
			system("CLS");
			main();
		}
	}
	
}

void payment() {
	int paymentNum1, paymentNum2, paymentNum3, paymentNum4;
	char firstname[50];
	char lastname[50];
	int paymentMethod1;
	int sum1 = 0 , sum,sum2,sum3;
	printf("This is your order:\n");
	for (int a = 0; a < counter1; a++) {
		printf("%dx %s\n", foodQuantity[a], food[foodOrder[a] - 1]);
		sum2 = foodPrice[foodOrder[a]-1];
		sum3 = foodQuantity[a];
		sum = sum3 * sum2;
		sum1 += sum;
	}
	printf("Total Price: %dK\n", sum1);

	printf("Your First Name:\n");
	scanf("%s", &firstname);
	printf("Your Last Name:\n");
	scanf("%s", &lastname);
	printf("1.Cash\n2.Credit Card or Debit Card\n");
	printf("Select payment method:");
	scanf("%d", &paymentMethod1);
	if (paymentMethod1 == 2) {
		printf("Insert Credit/debit card number(16 digit):\n");
		scanf("%d %d %d %d", &paymentNum1, &paymentNum2, &paymentNum3, &paymentNum4);
	}
	FILE* wo = fopen("order.txt", "w");

	fprintf(wo, "Order By: %s %s\n", firstname, lastname);
	if (paymentMethod1 == 1) {
		fprintf(wo, "Payment Method: Cash\n");
	}
	else{
		fprintf(wo, "Payment method: debit/credit card- %d\n", paymentNum4);
}
	fprintf(wo,"Order:\n");
	for (int a = 0; a < counter1; a++) {
		fprintf(wo,"%dx %s\n", foodQuantity[a], food[foodOrder[a] - 1]);

	}
	fprintf(wo,"Total Price: %dK\n", sum1);
	fclose(wo);
	printf("Your order has been processed and will be sent soon!\nThank you for Choosing us!\n");
	printf("Reverting back to main menu...\n");
	printf("\n");
	longDelay();
	system("CLS");
	main();
	exit(0);
}

void asciiART() {

	FILE* fileArt = fopen("asciiART.txt", "r");
	char a;
	while (fscanf(fileArt, "%c", &a) != EOF) {
		printf("%c", a);
	}
	printf("\n");
	fclose(fileArt);

}

