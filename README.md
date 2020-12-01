# VRLocomotion

In the default UE4 camera component, the camera can either snap to the location and rotation of the Head Mounted Display, or neither. The camera snapping to the location means the camera component inside the character moves independantly from the actor. This is useable for a teleportation based movement system, provided you attach everything to do with the character to the camera, but is very unhelpful when you want joystick based movement. It's also pretty unhelpful for more complicated setups, where the character may need to rely on their capsule component.

This plugin aims to fix that, implementing an extention of the camera component, the VRCamera Component, which changes makes it so the lock option only locks the rotation, and not the Location (though the tool tip is still the same, I extended the camera and overrided the function related to the camera, so I couldn't change the tooltip message). This means the camera will stay in it's place, but still orientate with HMD, this allows custom logic to be setup in the character to move the character with the HMD, which has been implemented in this plugin as the VRLocomotion Character.

Feel free to use this for your projects.
