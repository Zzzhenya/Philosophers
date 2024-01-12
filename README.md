# Modified version of Edsger Dijkstra's Dining philosophers problem

1) Why mutex for printing to stdout?

	To print action timestamps in order of calling printf.
	

2) Why mutex for dead check ? 

	To stop as soon as a thread updates the status, without printing any
	status of other live threads/philosophers.

