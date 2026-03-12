int error(void)
{
	write(2, "error\n", 6);
	exit(1);
}