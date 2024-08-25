import { useState } from "react";
import { Button } from "~/components/ui/button";
import { Input } from "~/components/ui/input";
import { api, type RouterOutputs } from "~/trpc/react";

export function Post({
  post,
  userId,
}: {
  post: RouterOutputs["post"]["all"][number];
  userId: string;
}) {
  const [newPostText, setNewPostText] = useState(post.text);
  const [isEditing, setIsEditing] = useState(false);
  const utils = api.useUtils();
  const deletePost = api.post.delete.useMutation({
    async onSuccess() {
      await utils.post.all.invalidate();
    },
  });
  const updatePost = api.post.update.useMutation({
    async onSuccess() {
      await utils.post.all.invalidate();
      setIsEditing(false);
    },
  });

  return (
    <li>
      {isEditing ? (
        <form
          className="mb-2"
          onSubmit={(e) => {
            e.preventDefault();
            updatePost.mutate({ id: post.id, text: newPostText });
            setIsEditing(false);
          }}
        >
          <Input
            value={newPostText}
            onChange={(e) => setNewPostText(e.target.value)}
          />
        </form>
      ) : (
        <div className="mb-2">
          <p>{post.text}</p>
          <p>
            Posted by{" "}
            <span className="font-semibold">
              {userId === post.userId ? "you" : (post.user.handle ?? "anon")}
            </span>
          </p>
        </div>
      )}
      {post.user.id === userId && (
        <div className="space-x-2">
          <Button
            onClick={() => {
              if (isEditing) {
                updatePost.mutate({ id: post.id, text: newPostText });
              } else {
                setIsEditing(true);
              }
            }}
            disabled={
              updatePost.isPending || (newPostText === post.text && isEditing)
            }
          >
            {isEditing ? (updatePost.isPending ? "Saving..." : "Save") : "Edit"}
          </Button>
          {isEditing && (
            <Button
              onClick={() => {
                setIsEditing(false);
              }}
            >
              Cancel
            </Button>
          )}

          <Button
            onClick={() => {
              deletePost.mutate(post.id);
            }}
            disabled={deletePost.isPending}
          >
            {deletePost.isPending ? "Deleting..." : "Delete"}
          </Button>
        </div>
      )}
    </li>
  );
}
