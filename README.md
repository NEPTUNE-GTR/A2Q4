# The Bounded buffer problem

The bounded buffer problem, aka the producer consumer problem, is a classic multi-process synchronization problem. 

My solution to this problem uses two pthread condition variables, and a single mutex lock.

The goal being that no process should consume from an empty buffer and that no process should produce(insert) into an already full buffer.
