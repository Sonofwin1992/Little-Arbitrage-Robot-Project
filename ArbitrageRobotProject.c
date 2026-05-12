#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Asset {
    char *ticker;          // Asset name 
    double *price_history; // Past prices
    int history_size;      // This asset how many times had price changing
} asset;

typedef struct Portfolio {
    char *owner_name;      
    int total_assets;      
    asset *assets;         
} portfolio;


// As you mean portfolio creater in heap region
portfolio* create_portfolio(char *owner, int asset_count);

// adjust each asset
void initialize_asset(portfolio *p, int index, char *ticker_name, int hist_size);

// deallocatings
void destroy_portfolio(portfolio *p);
int main() {
	char oName[50];
	int assetCounts;
	printf("Enter portfolio name then asset counts: ");
	scanf("%s%d", oName, &assetCounts);
	portfolio *myPort = create_portfolio(oName, assetCounts);
	int i;
	for(i = 0; i < assetCounts; i++) {
		char tickerName[50];
		int price_hist_size;
		printf("\nEnter values in order of ticker name, how many times the price changed for %d. asset: ", (i+1));
		scanf("%s%d", tickerName, &price_hist_size);
		initialize_asset(myPort, i, tickerName, price_hist_size);
		int j;
		for(j = 0; j < price_hist_size; j++) {
			printf("\nEnter %d. price of %d. asset: ", (j+1), (i+1));
			scanf("%lf", &myPort->assets[i].price_history[j]);
		}
	}
	destroy_portfolio(myPort);
	return 0;
}
portfolio* create_portfolio(char *owner, int asset_count) {
	portfolio *myPortfolio = (portfolio *)malloc(sizeof(portfolio));
	if(myPortfolio == NULL) {
		puts("Out of memory!");
		exit(0);
	}
	myPortfolio->total_assets = asset_count;
	myPortfolio->owner_name = (char *)malloc(strlen(owner) + 1);
	if(myPortfolio->owner_name == NULL) {
		puts("Out of memory!");
		exit(0);
	}
	strcpy(myPortfolio->owner_name, owner);
	myPortfolio->assets = (asset *)calloc(asset_count, sizeof(asset));
	if(myPortfolio->assets == NULL) {
		puts("Out of memory!");
		exit(0);
	}
	return myPortfolio;
}
void initialize_asset(portfolio *p, int index, char *ticker_name, int hist_size) {
	p->assets[index].ticker = (char *)malloc(strlen(ticker_name) + 1);
	if(p->assets[index].ticker == NULL) {
		puts("Out of memory!");
		exit(0);
	}
	p->assets[index].history_size = hist_size;
	strcpy(p->assets[index].ticker, ticker_name);
	p->assets[index].price_history = (double *)calloc(hist_size, sizeof(double));
	if(p->assets[index].price_history == NULL) {
		puts("Out of memory!");
		exit(0);
	}
}
void destroy_portfolio(portfolio *p) {
	int i;
	for(i = 0; i < p->total_assets; i++) {
		free(p->assets[i].ticker);
		p->assets[i].ticker = NULL;
		free(p->assets[i].price_history);
		p->assets[i].price_history = NULL;
	}
	free(p->assets);
	p->assets = NULL;
	free(p->owner_name);
	p->owner_name = NULL;
	free(p);
	p = NULL;
}
