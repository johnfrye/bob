#include "torch5spro.h"

using namespace Torch;

///////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	char* in_videoname = 0;
	char* dir_images = 0;
	char* out_videoname = 0;
	bool verbose = false;
	bool oi = false;
	bool ov = false;
	int n_images = -1;

	// Read the command line
	CmdLine cmd;
	cmd.info("Testing program for reading & writing videos.\n");
	cmd.addSCmdArg("in_video", &in_videoname, "input video");

	cmd.addText("Options:");
	cmd.addICmdOption("-I", &n_images, 0, "number of images to process");
	cmd.addBCmdOption("-oi", &oi, false, "output individual images");
	cmd.addSCmdOption("-dir_images", &dir_images, "./", "directory to save each frame");
	cmd.addBCmdOption("-ov", &ov, false, "output the video");
	cmd.addSCmdOption("-out_video", &out_videoname, "output.avi", "output video filename");
	cmd.addBCmdOption("-verbose", &verbose, false, "verbose");

	cmd.read(argc, argv);

	// Open the input/output videos for reading/writing
	Video in_video, out_video;
	in_video.setBOption("verbose", verbose);
	if(ov) out_video.setBOption("verbose", verbose);

	CHECK_FATAL(in_video.open(in_videoname, "r") == true);
	//if (verbose)
	{
		print("Input video: [%dx%d], %f bitrate, %f framerate, %d gop, %d frames [%s].\n",
			in_video.getIOption("width"),
			in_video.getIOption("height"),
			in_video.getFOption("bitrate"),
			in_video.getFOption("framerate"),
			in_video.getIOption("gop"),
			in_video.getNFrames(),
			in_video.codec());
	}

	if(ov)
	{
		CHECK_FATAL(out_video.setIOption("width", in_video.getIOption("width")) == true);
		CHECK_FATAL(out_video.setIOption("height", in_video.getIOption("height")) == true);
		CHECK_FATAL(out_video.setFOption("bitrate", in_video.getFOption("bitrate")) == true);
		CHECK_FATAL(out_video.setFOption("framerate", in_video.getFOption("framerate")) == true);
		CHECK_FATAL(out_video.setIOption("gop", in_video.getIOption("gop")) == true);

		CHECK_FATAL(out_video.open(out_videoname, "w") == true);
	}

	// Load each frame from the input video, save it and write it to the output video
	Image image(1, 1, 3);	// This will read RGB images!!! (no matter what the input video frames)
	//Image image(1, 1, 1);	// This will read grayscale images!!! (no matter what the input video frames)

	int cnt_frames = 0;
	while (in_video.read(image) == true)
	{
		cnt_frames ++;
		print(">>> reading [%d/%d] ...\r", cnt_frames, in_video.getNFrames());

		if(oi)
		{
			static xtprobeImageFile xtprobe;
			char imagename[1024];
			sprintf(imagename, "%s/frame%d.jpg", dir_images, cnt_frames);
			CHECK_FATAL(xtprobe.save(image, imagename) == true);
		}

		if(ov) CHECK_FATAL(out_video.write(image) == true);

		if(cnt_frames == n_images) break; 
	}

	//CHECK_FATAL(cnt_frames == in_video.getNFrames());

	// Close the videos
	in_video.close();
	out_video.close();

	print("\nOK\n");

	return 0;
}

