libbsdl
=======

My experimental library for reading BSDL (Boundary Scan Definition Library). 
I hope eventually it will be used by OpenOCD and others. I have also been 
toying with the idea of using it in a much more limited way to generate 
symbols for gEDA and friends. In a much longer term there ar a number of 
people who want an open source VHDL tool and BSDL is derivative of VHDL. I 
can imagine later on people resusing the source code to create a VHDL 
preprocessor.

All of that is just musing at this point. I have a lot more programming to 
do before this is usable for anything. I wanted to work the programming 
from the bottom up instead of top down. The idea is first to get the file 
into a data structure that can be easily traversed. This is the job of the 
preprocessor. Then the file can be closed and the data structure can be 
handed over to one or more post processor tools operated by the program 
calling libbsdl. 

The reason for this and not implimenting a simple grep like function of 
the bsdl file is that you can include some state machine information in 
the files and basic associations between variables, constants and etc. 
The result is that this is that the content of the file has to be treated 
more like a hybrid of code and listing of chip features and details. 

It is worth noting that there are a lot of things that are optional in 
the BSDL standard and a lot of vendors do not really believe in being 
complaint with that standard. I could say garbage in garbage out but I 
think in the long term it would be more sensible to craft some kind of 
post process tool in the library that reports back what if any complaince 
the bsdl file has. That way the tool calling the library can ask the user 
to make the call about how the information in it should be interprited. I 
have no experiance using higher end or what you might call professional 
level JTAG or boundary scan tools so I have no idea how this is handled 
by others.

For a language meant to enable automated test there is a lot of user 
involvement in using a BSDL file. The DESIGN_WARNING stuff is all on the 
user to read. Likewise there are files where simple things like chip 
package/footprint effect pinout and the file includes all variations 
with the expectation that the user will pick the correct one. To me this 
is nuts but I am sure the IEEE had their reasons. I have been told that 
being on those standards groups can be hard.

Right now this is the vision of the libraries internal workings. Try 
to picture the file on the left side and the world after the library on 
the right.

   /-----------------------libbsdl--------------------\
   |						      |
   |  /-------------\   /------\   /--------------\   |
-->|->|fpreprocessor|-->|memory|-->|fpostprocessor|-->|-->
   |  \-------------/   \------/   \--------------/   |
   |						      |
   \--------------------------------------------------/

Eventually though I would like to have this. Notice there is no prevision 
for access to the raw text. If you want to edit then open a text editor.

   /-----------------------------libbsdl-----------------------------\
   |								     |
   |	    /---------\				/----------\	     |
   |	 -->|fpreproc.|>---		     -->|fpostproc.|>---     |
   |	/   \---------/	   \		    /	\----------/	\    |
   |   /		    \   /------\   /			 \   |
<---->*			     *<>|memory|<>*			  *<---->
   |   \		    /   \------/   \			 /   |
   |	\   /----------\   /		    \   /---------\	/    |
   |	 --<|bpostproc.|<--		     --<|bpreproc.|<----     |
   |	    \----------/			\---------/	     |
   |								     |
   |			/---------------------\			     |
   |			| internal com. code  |			     |
   |			|(ex. string handling)|			     |
   |			\---------------------/			     |
   \-----------------------------------------------------------------/

How do I want to use it in the short term? Well I picture something like 
this. Two parallel workflows one for gEDA and the other for openocd.

                           /---------User Land--------\

   /-------\   /-------\   /--------\	/-------------\
-->|libbsdl|>->|edacore|>->|bsdl2sym|>->|gschem & etc.|
   \-------/   \-------/   \--------/	\-------------/

   /-------\				/-------\
-->|libbsdl|<-------------------------->|openocd|
   \-------/				\-------/

Eventually the idea would be add an aditional workflow to do this for 
KiCad. (Please note I leave it to someone else more familiar with the 
KiCad codebase to add this. I don't even know if this graph makes sense 
given their architecture.)

   /-------\   /-------\   /----------\   /-----\
-->|libbsdl|>->|edacore|>->|bsdl2kisym|>->|KiCad|
   \-------/   \-------/   \----------/   \-----/

Now this bit really excites me even though it will probably only be used 
by a handfull of users. I really want to do this.

   /-------\		 /-------\       /-------------\     /------\
-->|libbsdl|<----------->|openocd|<~~~~~>|gschem plugin|<--->|gschem|
   \-------/             \-------/

Note: The ~ is meant to symbolize IP traffic instead of regular flow.

This is GPL V2 licensed but you can bump that up to V3. Not to kick off a 
holy war here but I am not a big fan of GPL V3. I only ask that people 
please don't do it.


