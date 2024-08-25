import { useState } from "react";
import { Button } from "~/components/ui/button";
import { Input } from "~/components/ui/input";
import { api, type RouterOutputs } from "~/trpc/react";

export function Post({
  post,
  userId,
}: {
  post:
    | RouterOutputs["post"]["all"][number]
    | RouterOutputs["post"]["allReplies"][number];
  userId: string;
}) {
  const replies = api.post.allReplies.useQuery(post.id);
  const [newPostText, setNewPostText] = useState(post.text);
  const [replyText, setReplyText] = useState("");
  const [isEditing, setIsEditing] = useState(false);
  const [isReplying, setIsReplying] = useState(false);
  const utils = api.useUtils();
  const deletePost = api.post.delete.useMutation({
    async onSuccess() {
      await utils.post.invalidate();
    },
  });
  const updatePost = api.post.update.useMutation({
    async onSuccess() {
      await utils.post.invalidate();
      setIsEditing(false);
    },
  });
  const replyToPost = api.post.reply.useMutation({
    async onSuccess() {
      await utils.post.allReplies.invalidate(post.id);
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
        <div className="mb-2 space-x-2">
          <Button
            onClick={() => {
              if (isReplying) {
                setIsReplying(false);
              } else {
                setIsReplying(true);
              }
            }}
          >
            {isReplying ? "Cancel Reply" : "Reply"}
          </Button>
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
      {isReplying && (
        <form
          className="mb-2"
          onSubmit={(e) => {
            e.preventDefault();
            replyToPost.mutate({
              text: replyText,
              replyToId: post.id,
            });
            setIsReplying(false);
          }}
        >
          <div className="flex items-center gap-2">
            <span>{">"}</span>
            <Input
              placeholder="Enter your reply text"
              value={replyText}
              onChange={(e) => setReplyText(e.target.value)}
            />
          </div>
        </form>
      )}
      {replies.data && replies.data.length > 0 && (
        <ul className="ml-6">
          {replies.data.map((reply) => (
            <Post key={reply.id} post={reply} userId={userId} />
          ))}
        </ul>
      )}
    </li>
  );
}
