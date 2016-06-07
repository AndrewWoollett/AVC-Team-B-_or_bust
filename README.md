# AVC-Team-B-_or_bust
Team repository for the AVC Project in ENGR101.
Team members include: David Scott, Daniel Sommerville, Ana Ramirez, Daniel Van Eijck and Andrew Woollett


Week 1 Plan (22nd April, just before the holidays/during the holidays)
Andrew: Set up the Github repository
David: Go over the AVC plan to make sure everything is completed
Daniel: SSH into the RPi
Daniel S: Put together the initial hardware components
Ana: Create weekly plan (table) and get key dates and people organised

Week 1 Review:
(Since it was the holidays, we only set up very simple goals as we knew we would not be able to complete much while away from uni).
Everyone completed their respective tasks for this week and we got the AVC plan in on time before the holidays.

Week 2 Plan (28th April, During and after the holidays):
(Minor work as part of this week is during the holidays and wouldnt be able to organise team meetings)
Andrew: Review and go over the skeleton code
David: Planning of the code to get the sensor working
Daniel V: Planning the code to get the robot working
Daniel S: Startng designing hardware construction
Ana: Arrange communication, sorting out meetings outside of lab time.

Week 2 Review:
Because of the holidays, again we couldn't get a lot done in terms of coding, but we did as a group go over the skeleton code and began planning how to go about building on the skeleton code to get the basic function of the robot working.
Daniel made a full detailed plan of the design and hardware of the robot that he created on Blender. He had also already 3D printed a few of the basic components of the hardware.
Daniel V, Andrew, and Ana had a few problems with SSH-ing into the Rpi and finding the IP address, but this was just through simple errors of our own, rather than technical issues with the RPi.

Week 3 Plan (5th May):
Andrew: Begin coding to get the sensors working so that the basic "detection" part of the robot is operational
David: Continue producing documentation and overseeing and providing help with software
Daniel V: With Andrew, begin coding to get the sensors working so that the basic "detection" part of the robot is operational and begin on the basic movement of the robot
Daniel S: Continue with the construction, design, and printing of the hardware to have it completed by the start of our next official lab time (12th May).
Ana: Arrange meetings and delegate tasks as well as assist with the documentation and software

Week 3 Review:
We had a few issues this week with our RPi. On Friday, our robot short circuited, we believe because Daniel was constructing the robot while it was still turned on, resulting in a lot of our planned meeting time being used by trying to fix it. In the end, we had a to ask Elf for help, who gave us a new SD card.
This meant that we lost a lot of the code that we'd been working on since we were working on the Pi itself and hadn't uploaded any of the code to GitHub. Because of this, we've had to work significantly harder this week in order to regain our lost time and files.
Aside from our issues, Daniel S successfully completed printing out all the hardware and construction of the robot so that it is practical and functional, yet follows the "aesthetic" requirements of the project.
Andrew and Daniel S have both been working on regaining and improving the code that we have lost, with assistance from David and Ana. At the end of this week we have committed and saved and committed several files to GitHub for the software, but haven't actually run or tested anything yet, which we plan to do in our next meeting (12th May).

Week 4 Plan (12th May):
As an overall goal as a group, by our next designated lab time, we aim to be testing our robot on the official board, and hopefully be running the robot up to the B- mark (end of the second quadrant).
Andrew: Develop the code to enable the robot to turn at dead ends
David: Continue with documentation and assist with developing the code to get the robot to turn around the curved corners
Daniel V: Develop the code to enable the robot to turn at dead ends
Daniel S: Design a new back wheel and figure out a way for the robot to fit turn inside the maze.
Ana: Continue with documentation and assist with developing the code to get the robot to turn around the curved corners, as well as go over the code to get the gate opening (written by Daniel V), test it, and get it functional.

Week 4 Review (so far):
David has not showed up for our Thursday lab or the extra meeting we scheduled on Friday (absence yet to be explained).
Daniel S put the finishing touches on the hardware of robot, so that this part is complete so we are now free to run code on the robot to test it officially. We ran into a few problems when trying to test our code, one of them being that our RPi didn't have the lt and makefile files. So we asked Arthur and he gave us another updated SD card (again) with the correct files on it this time. By the end of Thursday's lab we had the robot moving and operational. It could roughly dectect a line and attempts very roughly to rectify itself back onto the line when it goes astray, however, we are still very pleased with this progress.
After our extra meeting on Friday (attended by Daniel V, Daniel S, and Ana), we made even further progress. We haven't got the gate working yet as we have been concentrating on getting the robot to follow the path, which at the moment it successfully does up until the second curve in the path (it can get through the first curve as it is not as sharp as the second curve).
By the end of the week (on Thursday the 19th), the robot was able to complete up to the B- mark on the path, meaning that one of our main goals was achieved. We also managed to fix the problem of the robot tipping over when it reversed (because of weight distribution), by relocating the placement of the battery on the robot. We noted that the back wheel of our robot was slightly faulty and meant that the robot occasionally went off on the wrong direction, so we made the plan to replace this wheel with a marble so it is able to move more freely. Daniel wrote down a lot of his testing process this week in order to get the camera sensing the line properly in order to get it up to the B- mark, as well as figuring out how to deal with T junctions and dead-ends. This documentation can be found in the document “Daniel’s Documentation (week 4)”


Week 5 plan (19th May): Our overall group goal this week is to get the robot operational up to the entrance to the maze, and have a plan of how to code the maze. 
Daniel V and Daniel S: refine code further so that the robot is able to deal with right angled turns, T junctions, and dead ends, so that the robot can reach the entrance of the maze.
Ana: Continue with the documentation.
David, Andrew, and Ana: begin researching and working on a plan of how to get the robot to complete the maze.

Week 5 Review: this week we kept running into the regular problem of the lab being constantly full, so much so that we weren’t allowed in unless it was our regular lab time, or that only1 or 2 members of the team were allowed in at once. In this situation of only a few team members being allowed in at once, we decided to place getting the robot up to the entrance of the maze as a priority over beginning working on the maze code, which meant that we didn’t advance very quickly with our maze code this week. However, by the end of the week, we successfully got the robot reaching the entrance of the maze with around 80% consistency. PID just needs to be refined further in order to get this working. And we did end up with a general plan on how to tackle the maze code, and managed to get the sensors to detect the red square at the start of the maze, so that the sensors are activated.

Week 6 plan (26th May): We predict that since this is the final week of the AVC until it is tested, the lab will be packed almost all the time, so our only options are to get in early, or to work on code outside the lab. We are currently feeling very confident about our robot, so we have set the goal of the robot completing 100% of the maze by the time it comes to be tested.
Daniel V: refine PID so that the robot is able to follow the tape more consistently.
Rest of the team: create the Maze code and the PID for the sensors.

Week 6 Review: As we predicted, it is very difficult this week to get spots in the lab, so we ended up meeting outside the lab to create some basic maze code that we would test on the robot at our next opportunity. This rough code worked very well as a starter, so from here we began to create the PID for the robot. Daniel V refined the code further so that it could get up to the entrance of the maze much faster and at a more consistently. However, an issue keeps coming up where at the first right angled junction (before the B- mark), the robot goes into the dead end, and to escape it, it reverses, and then retraces its steps, back to the start of the maze. This occurs probably 40% of the time, and we’ve decided that there’s nothing much we can do about it, and it will be ok, especially since during the final testing, we are allowed to restart the robot as many times as we want within those 15 minutes. After implementing the maze PID, we had a few errors were occasionally the robot would get stuck on a corner, but improving PID fixed this issue fairly easily. By Tuesday the 31st (2 days before our final test), the robot was able to fully complete all 4 quadrants fairly consistently and at a decent speed. On Thursday, our robot was officially tested, and completed 100% of the maze, sending us to an A+, in 1 minute 5 seconds, a time and grade that we were all very happy with, and because of this, we made it into The AVC finals, to face off against the rest of the highest scoring robots.
