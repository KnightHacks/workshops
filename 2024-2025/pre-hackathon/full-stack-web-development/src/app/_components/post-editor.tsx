"use client";

import { useState } from "react";
import { Button } from "~/components/ui/button";
import { Textarea } from "~/components/ui/textarea";
import { api } from "~/trpc/react";

export function PostEditor() {
  const [postText, setPostText] = useState("");
  const createPost = api.post.create.useMutation();

  return (
    <div className="mb-2">
      <h1 className="mb-2">Post Editor</h1>
      <form
        onSubmit={(e) => {
          e.preventDefault();
          createPost.mutate(postText);
          setPostText("");
        }}
      >
        <Textarea
          className="mb-2"
          placeholder="Enter your post text"
          value={postText}
          onChange={(e) => setPostText(e.target.value)}
        />
        <Button type="submit">
          {createPost.isPending ? "Creating post..." : "Create Post"}
        </Button>
      </form>
    </div>
  );
}
