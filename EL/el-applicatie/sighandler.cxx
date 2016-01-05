#include <iostream>
#include <signal.h>

#include "sighandler.hxx"

static void handler(int sig, siginfo_t *si, void *unused)
{
	std::cout << "Iets doet het niet maar oke we gaan wel door!2" << std::endl;
	exit(0);
}

void install_sig_handler()
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	if (sigaction(SIGSEGV, &sa, NULL) == -1)
	{
		std::cout << "Iets doet het niet maar oke we gaan wel door!" << std::endl;
	}
}