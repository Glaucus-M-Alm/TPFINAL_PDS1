#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


#define NUM_PRATOS 8

const float FPS = 100;  

const int SCREEN_W = 960;
const int SCREEN_H = 540;

//largura do jogador
const float JOGADOR_W = 50;
const float JOGADOR_H = 100;
const float PRATO_W = 60;
const float PRATO_H = 20;
const float POLE_W=20;
const float POLE_H= 200;

typedef struct Jogador {
	
	float x;
	int equilibrando;
	int mov_esq, mov_dir;
	ALLEGRO_COLOR cor;
	float vel;
	
} Jogador;

typedef struct Prato {
	float x;
	
	/* um valor entre 0 e 255, em que 0 = prato equilibrado e
	   1 = prato com maxima energia, prestes a cair */
	float energia;
	float tempoParaAparecer;
	
} Prato;

typedef struct Poste{
	//int poleSpacing; //= SCREEN_W/ poleCount;//espaço entre um poste e outro//SCREEN_H-100, poleWidth=50;//altura de cada poste
	int X;//posição x de um poste
		 /*for (i = 0; i < poleCount; i++) {
		poleX=i*poleSpacing;
        al_draw_filled_rectangle(poleX, 100, poleX + poleWidth, poleHeight, al_map_rgb(255, 255, 255));}*/
} Poste;

void desenha_cenario() {
	ALLEGRO_COLOR BKG_COLOR =al_map_rgb(0,177,240);
	//colore a tela de branco (rgb(255,255,255))

	al_clear_to_color(BKG_COLOR); 
    }
void desenha_postes(Poste postes[]){
	int i=0;
	while(i<NUM_PRATOS){
	al_draw_filled_rectangle(postes[i].X,POLE_H+250,postes[i].X+POLE_W,POLE_H,al_map_rgb(0, 0, 0));
	i++;
		}
	}
void desenha_jogador(Jogador j) {
	
	al_draw_filled_triangle(j.x, SCREEN_H - JOGADOR_H, 
							j.x - JOGADOR_W/2, SCREEN_H,
							j.x + JOGADOR_W/2, SCREEN_H,
							j.cor);	
	
}

void atualizaJogador(Jogador *j) {
	if(j->mov_esq) {
		if(j->x - j->vel > 0)
			j->x -= j->vel;
	}
	if(j->mov_dir) {
		if(j->x + j->vel < SCREEN_W)
			j->x += j->vel;
	}	
}


void InicializaJogador(Jogador *j) {
	j->x = SCREEN_W / 2;
	j->equilibrando = 0;
	j->cor = al_map_rgb(0, 223, 15);
	j->mov_esq = 0;
	j->mov_dir = 0;
	j->vel = 1;
}

float geraTempoPrato(int i) {
	return i+1;
}

void inicializaPratos(Prato pratos[], Poste postes[]) {
	
	//CONSERTAR ESTA FUNCAO!
	
	int i;
	//int plateSpacing = SCREEN_W/ (NUM_PRATOS);
	for(i=0; i<NUM_PRATOS; i++) {
		pratos[i].x = (i*SCREEN_W/(NUM_PRATOS))+40;
		pratos[i].tempoParaAparecer = geraTempoPrato(i);
		pratos[i].energia = 255;
		postes[i].X=(i*SCREEN_W/(NUM_PRATOS))+60;

	}

}
void aparece_prato(int *appear){//cria o vetor com os tempos para aparecer cada prato
	int i;
	if(NUM_PRATOS%2==0){
		for(i=0;i<NUM_PRATOS/2;i++){
			appear[i]=NUM_PRATOS-(2*i+1);
			appear[NUM_PRATOS/2+i]=2*(i+1);
		}
	}else{
				for(i=0;i<=NUM_PRATOS/2;i++){
					appear[i]=NUM_PRATOS-(2*i+1);
					appear[NUM_PRATOS/2+i+1]=2*(i+1);
	}			for(i=0;i<NUM_PRATOS/2;i++){
					appear[i]=NUM_PRATOS-(2*i+1);
					appear[NUM_PRATOS/2+i]=2*i+1;
}
				appear[NUM_PRATOS/2]=1;
				appear[NUM_PRATOS-1]++;
}

}
void desenha_pratos(Prato pratos[],ALLEGRO_TIMER *timer,int Apare[]){//desenha os pratos gradativamente
	int i,t;
	t=(int)al_get_timer_count(timer);
	for(i=0;i<NUM_PRATOS;i++){
		if(t>=Apare[i]*100){
			al_draw_filled_rectangle(pratos[i].x,PRATO_H+180,pratos[i].x+PRATO_W,PRATO_H+170,al_map_rgb(255, 255, 255));
		}
	}
}
void atualiza_prato(Prato *prato){//desenha os pratos gradativamente

			al_draw_filled_rectangle(prato->x,PRATO_H+180,prato->x+PRATO_W,PRATO_H+170,al_map_rgb(255, prato->energia,prato->energia));

	}
int chec_pos(Jogador *player, Poste *postes){//checa se o jogador está em um x específico
	int i;
	for(i=0;i<NUM_PRATOS;i++){
		if(player->x+JOGADOR_W/2>=postes[i].X&&player->x- JOGADOR_W/2<=postes[i].X+POLE_W){
			return i;
		}
		}
		return -1;
	}
void pontos(ALLEGRO_TIMER *timer, ALLEGRO_FONT *font, int *s){
	*s=(int)al_get_timer_count(timer);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Pontos: %d", *s);
}

 void cai_prato(Prato *prato){//desenha os pratos gradativamente

			al_draw_filled_rectangle(prato->x,PRATO_H+450,prato->x+PRATO_W,PRATO_H+440,al_map_rgb(255, prato->energia,prato->energia));

	}
	void ponto_final(ALLEGRO_FONT *font, int s, int recorde){
		al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 90, ALLEGRO_ALIGN_CENTER, "Pontos: %d", s);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 130, ALLEGRO_ALIGN_CENTER, "Recorde: %d", recorde);
	}
int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;	
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}	
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}	
	
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}	
	
	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	ALLEGRO_KEYBOARD_STATE teclado;
	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}	
	
	
 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}	
	
	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 	
	
	
	//JOGADOR
	Jogador jogador;
	InicializaJogador(&jogador);
	
	//PRATOS e Postes
	Prato pratos[NUM_PRATOS];
	Poste postes[NUM_PRATOS];
	inicializaPratos(pratos, postes);
	//fonte para os pontos durante o jogo
	ALLEGRO_FONT *font = al_create_builtin_font();
	//inicializando a ordem em que os pratos aparecerão
	int Apare[NUM_PRATOS];
	aparece_prato(Apare);
	//algumas variáveis utilizadas durante o jogo
	int i, caido, p, recorde;
	int *s;
	s=&p;
	int playing=1;
	
	//inicia o temporizador
	al_start_timer(timer);	
	
	while(playing) {
		
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);
		
		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

		
			desenha_cenario();
			desenha_postes(postes);
			desenha_pratos(pratos,timer,Apare);
				for(i=0;i<NUM_PRATOS;i++){
					if((int)al_get_timer_count(timer)>=Apare[i]*100){
				pratos[i].energia -= 0.1;
				atualiza_prato(&pratos[i]);		
				if(pratos[i].energia<=0){
					caido=i;
					playing=false;
				}}
			}
			pontos(timer,font,s);
			atualizaJogador(&jogador);
			
			desenha_jogador(jogador);

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}		
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			//imprime qual tecla foi
			//printf("\ncodigo tecla: %d", ev.keyboard.keycode);
			
			if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
				jogador.mov_esq = 1;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
				jogador.mov_dir = 1;
			}else if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
				i=chec_pos(&jogador,postes);
				if(i!=-1){
					//for(i=0;i<NUM_PRATOS;i++){
					if(pratos[i].energia<255){
						pratos[i].energia+=10;
						atualiza_prato(&pratos[i]);
					}
				}
			}
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {

			if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
				jogador.mov_esq = 0;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
				jogador.mov_dir = 0;
			}
						
		}		
		
}
bool fall=true;
	Prato prato_caido = pratos[caido];
	FILE *scoreFile = fopen("recorde.txt", "r+");
    if (!scoreFile) {
        fprintf(stderr, "Failed to open score file!\n");
        return -1;
    }
	//associa o valor que estiver no arquivo ao recorde
	fscanf(scoreFile, "%d", &recorde);
	
	//checa se a pontuação é maior que o recorde
	if(p>recorde){
		recorde=p;
		fseek(scoreFile, 0, SEEK_SET);
		fprintf(scoreFile, "%d", recorde);
	}
	while(fall)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		double tempo = al_get_timer_count(timer);
		if(evento.type == ALLEGRO_EVENT_TIMER)
		{
			desenha_cenario();
			desenha_postes(postes);
			cai_prato(&prato_caido);
			desenha_jogador(jogador);
			ponto_final(size_32,p,recorde);	
			al_flip_display();

		}else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			fall = false;
		}
		}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	fclose(scoreFile);
 
	return 0;
}
