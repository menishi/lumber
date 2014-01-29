PLAN
====

Task 1: Next step we want to set the program create a logfile.

- DONE
------------------------------------------------------
Task 2: Next we want to built the switch command.

- DONE
------------------------------------------------------
Task 3: Now we want to create a deamon program that stores 
   the current log track and can switch stream when 
   the control program tells it to. We want to communicate 
   to it using a {pipe} [EDIT] using the loopback interface.

   Subtask 1: create a way to communicate with the process
      We will be using the loopback interface

   - DONE
   ---------------------------------------------------
   Subtask 2: I need to add all the necessary error catching 
      stuff to the program.
   - DONE 
------------------------------------------------------
Task 3: We also want to create a loadable configuration file.
   We should probably make this a cascading system. Adding
   the ability to add users to lumber tracking is another
   good idea. We will then check first that the user exists 
   then that we have permission to connect up that user. 
   Lumberd will run be active for all users. 
------------------------------------------------------
Task 4: We want to automatically place all package install commands
   into a single logfile as well as the default one.
