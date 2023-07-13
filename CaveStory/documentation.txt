Hi, autumn here!

Thank you for downloading this fmod dll. In this documentation txt file, we will specifically go over how to properly play/save your audio in-game.
This doesn't cover how to add audio, but this will cover how to properly play multiple tracks at once, and save them all to the save file.

################
# TSC Commands #
################

There are a few new TSC commands added in this fmod dll.
These include:

# <PEV - Play fmod EVent [<PEVstring$]

This TSC command has a custom argument ~ That being playing audio isn't an ID system like how Cave Story does things -> It's a text string!
All fmod events begin with "event:/", so every tsc command should start with "<PEVevent:/".

Place a "$" at the end of your event name for the game to know to stop reading text!

Example:
<PEVevent:/exampleaudio$
( The above will play the event name "exampleaudio" )

# <CEV - Change fmod EVent [<CEVxxxx]

This TSC command specifically tells the game that we want to play a different audio track on a different group.
There are 8 groups you can use, that being from 0-7.

This changes what group <PEV will play a track in -> By default it's 0.
This is also how the game knows what to save to the save file, so make sure if you wanna play an ambience track, you use this command first!

Example:
<CEV0001<PEVevent:/wind$<CEV0000
( The above will set the event group to "1", play the "event:/wind" ambience, and then set the group back to "0" )

# <SEV - Stop fmod Event [SEVxxxx]

This TSC command stops the currently playing event in X group.

For a more technical explanation, this automatically plays the track "event:/Null/null000x" depending on the group you set.

Example:
<SEV0000
( The above will stop playing the currently playing event in group 0 )

# <CVP (Change eVent Parameter) [<CVPstring$]

This TSC command will allow you to change the parameter used for <EVP.

Example:
<CVPprogress$
( The above will change the <EVP parameter to "progress" )

# <EVP (EVent Parameter) [<EVPxxxx]

This TSC command sets the currently set parameter by <CVP to a value of your choice.

This can be used to make progressional audio in your mod!

NOTE: Parameters aren't saved to the save file.

Example:
<EVP0001
( The above will set the current parameter to "1", the parameter itself being set by <CVP )