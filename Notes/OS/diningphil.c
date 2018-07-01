char state[n];		//Hungry, Thinking, Eating
int sema[n] = {0};

void philosopher(int i){
	think();
	takefork(i);
	eat();
	putfork(i);
}

void takefork(int i){
	lock(mutex);
	state[i] = 'H';
	test(i);
	unlock(mutex);
	down(sema[i]);
}

void putfork(int i){
	lock(mutex);
	state[i] = 'T';
	test(left);
	test(right);
	unlock(mutex);
}

void test(int i){
	if(state[i] = 'H' && state[left] != 'E' && state[right] != 'E'){
		state[i] = 'E';
		up(sema[i]);
	}
}
